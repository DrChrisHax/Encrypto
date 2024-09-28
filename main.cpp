#include <iostream>
#include <fstream>
#include <string>
#include "encrypto.hpp"

void clearTerminal() {
    //Compiles different based on OS
#ifdef _WIN32
    system("cls");
#else
    std::cout << "\033[H\033[J";
#endif
}

std::string getFileExtension(const std::string& filePath) {
    size_t dotPos = filePath.find_last_of('.');
    if (dotPos == std::string::npos) {
        return "";
    }
    return filePath.substr(dotPos + 1);
}

std::string getFileNameWithoutExtension(const std::string& filePath) {
    size_t dotPos = filePath.find_last_of('.');
    size_t sepPos = filePath.find_last_of("/\\");
    if (sepPos == std::string::npos) {
        sepPos = 0;
    } else {
        sepPos++;
    }
    if (dotPos == std::string::npos) {
        return filePath.substr(sepPos);
    }
    return filePath.substr(sepPos, dotPos - sepPos);
}

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
            //clearTerminal();
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
        //clearTerminal();
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
        //clearTerminal();
        std::cerr << "Error opening text file! Please enter a valid text file path:" << std::endl;
        std::cin >> textFilePath;
        textFile.open(textFilePath);
    }
    text.assign((std::istreambuf_iterator<char>(textFile)),
                 std::istreambuf_iterator<char>());
    textFile.close();

    uint32_t numKey = keyToNum(key);   

        if (bEncrypt) {
        std::string cipher = encrypt(text, numKey);
        std::string extension = encrypt(getFileExtension(textFilePath), numKey);

        std::ofstream outputFile("encrypted.txt");
        if (!outputFile) {
            std::cerr << "Error creating output file!" << std::endl;
            return 1;
        }

        // Save extension at the beginning
        outputFile << extension << '\n';
        outputFile << cipher;
        outputFile.close();

        std::cout << "Encryption completed. The cipher text has been saved to encrypted.txt" << std::endl;

    } else {
        std::ifstream inputFile("encrypted.txt");
        if (!inputFile) {
            std::cerr << "Error opening encrypted file!" << std::endl;
            return 1;
        }

        // Read the extension from the beginning
        std::string extension;
        std::getline(inputFile, extension);
        extension = decrypt(extension, numKey);

        // Read the rest of the file
        std::string cipher((std::istreambuf_iterator<char>(inputFile)),
                            std::istreambuf_iterator<char>());
        inputFile.close();

        std::string plaintext = decrypt(cipher, numKey);

        std::string outputFilePath = "plaintext." + extension;
        std::ofstream outputFile(outputFilePath);
        if (!outputFile) {
            std::cerr << "Error creating output file!" << std::endl;
            return 1;
        }
        outputFile << plaintext;
        outputFile.close();

        std::cout << "Decryption completed. The plaintext has been saved to " << outputFilePath << std::endl;
    }

    return 0;
}

//Key Gen Testing
// int main() {
//     std::cout << "test 0x" << std::hex << keyToNum("test") << std::endl;
//     std::cout << "TEST 0x" << std::hex << keyToNum("TEST") << std::endl;
//     std::cout << "key  0x" << std::hex << keyToNum("key") << std::endl;
//     std::cout << "aa   0x" << std::hex << keyToNum("aa") << std::endl;
//     std::cout << "a    0x" << std::hex << keyToNum("a") << std::endl;
//     std::cout << "b    0x" << std::hex << keyToNum("b") << std::endl;
//     std::cout << "c    0x" << std::hex << keyToNum("c") << std::endl;
//     std::cout << "d    0x" << std::hex << keyToNum("d") << std::endl;
//     std::cout << "e    0x" << std::hex << keyToNum("e") << std::endl;
//     std::cout << "f    0x" << std::hex << keyToNum("f") << std::endl;
//     std::cout << "     0x" << std::hex << keyToNum("") << std::endl; 
// }
