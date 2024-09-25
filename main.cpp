#include <iostream>
#include <fstream>
#include "encrypto.hpp"

int main(int argc, char* argv[]) {
    std::string key, text;
    std::string keyFilePath, textFilePath;
    bool bEncrypt; //1 for encryption, 0 for decryption

    if(argc == 4) {
        keyFilePath = argv[1];
        textFilePath = argv[2];
        
        char temp = argv[3][0] - '0';
        switch(temp) {
            case '\0':
                bEncrypt = 0;
                break;
            case '\1':
                bEncrypt = 1;
                break;
            default:
                std::cerr << "Usage: ./encrypto \"path_to_input\" \"path_to_key\" (0/1)";
                return 1;
        }
    } else {

        while(true) {
            std::string temp;
            std::cout << "Would you like to encrypt or decrypt? \n1. Encrypt \n2. Decrypt" << std::endl;
            std::cin >> temp;
            if(temp == "1") {
                bEncrypt = 1;
                break;
            } else if(temp == "2") {
                bEncrypt = 0;
                break;
            }
            std::cout << "Invalid option. Please select again." << std::endl;
        }

        std::cout << "Enter the key file path:" << std::endl;
        std::cin >> keyFilePath;
        std::cout << "Enter the text file path:" << std::endl;
        std::cin >> textFilePath;
    }

    //Get the Key
    std::ifstream keyFile(keyFilePath);
    while (!keyFile) {
        std::cerr << "Error opening key file! Please enter a valid key file path:" << std::endl;
        std::cin >> keyFilePath;
        keyFile.open(keyFilePath);
    }
    std::string line;
    while (std::getline(keyFile, line)) {
        key += line + "\n";
    }
    keyFile.close();

    //Get the text/cipher
    std::ifstream textFile(textFilePath);
    while (!textFile) {
        std::cerr << "Error opening text file! Please enter a valid text file path:" << std::endl;
        std::cin >> textFilePath;
        textFile.open(textFilePath);
    }
    text.assign((std::istreambuf_iterator<char>(textFile)),
                 std::istreambuf_iterator<char>());
    textFile.close();

    uint32_t numKey = keyToNum(key);   

    if(bEncrypt) {
       std::string cipher = encrypt(text, numKey);

        std::ofstream outputFile("encrypted.txt");
        if (!outputFile) {
            std::cerr << "Error creating output file!" << std::endl;
            return 1;
        }
        outputFile << cipher;
        outputFile.close();

        std::cout << "Encryption completed. The cipher text has been saved to encrypted.txt" << std::endl;

    } else {
        std::string plaintext = decrypt(text, numKey);

        std::ofstream outputFile("plaintext.txt");
        if (!outputFile) {
            std::cerr << "Error creating output file!" << std::endl;
            return 1;
        }
        outputFile << plaintext;
        outputFile.close();

        std::cout << "Decryption completed. The plaintext has been saved to plaintext.txt" << std::endl;
    }

    return 0;
}

