#include "encrypto.hpp"

//First 32-bits of the fractional parts of the cube roots of the first 16 primes
const unsigned int k[16] = {
	0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
	0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174
};

uint32_t keyToNum(const std::string &key) {

    uint32_t x = 0, i = 0;

    for(const char c : key) {
        x ^= (c ^ k[i % 16]);
        i++;
    }
    return x;
}

std::string encrypt(const std::string &text, const uint32_t key) {

    uint8_t bytes[4];

    bytes[0] = (key >> 24) & 0xFF;
    bytes[1] = (key >> 16) & 0xFF;
    bytes[2] = (key >> 8) & 0xFF;
    bytes[3] = key & 0xFF;

    std::string output = text;

    for(size_t i = 0; i < output.length(); ++i) {
        output[i] = swapBits(output[i] ^ bytes[i%4]) ^ k[i%16];
    }
    return stringToHex(output);
}

std::string decrypt(const std::string &text, const uint32_t key) {

    uint8_t bytes[4];

    bytes[0] = (key >> 24) & 0xFF;
    bytes[1] = (key >> 16) & 0xFF;
    bytes[2] = (key >> 8) & 0xFF;
    bytes[3] = key & 0xFF;

    std::string output = hexToString(text);

    for(size_t i = 0; i < output.length(); ++i) {
        output[i] = (swapBits(output[i] ^ k[i%16]) ^ bytes[i%4]);
    }
    return output;
}

char swapBits(char c) {
    //Swaps the first four bits and the second four bits
    char left = (c & 0xF0) >> 4;
    char right = (c & 0x0F) << 4;
    return (left | right);
}

std::string stringToHex(const std::string& input) {
    std::stringstream hexStream;
    int count = 0;

    for (char c : input) {
        hexStream << std::hex << std::setw(2) << std::setfill('0') << (int)(unsigned char)c;
        count += 2;

        if (count >= 32) {
            hexStream << '\n';
            count = 0;
        }
    }

    return hexStream.str();
}

std::string hexToString(const std::string& hexInput) {
    std::stringstream outputStream;

    for (size_t i = 0; i < hexInput.length(); i += 2) {
        // Skip newline characters
        if (hexInput[i] == '\n') {
            i--;
            continue;
        }
        
        std::string byteString = hexInput.substr(i, 2);
        char byte = (char) strtol(byteString.c_str(), nullptr, 16);
        outputStream << byte;
    }

    return outputStream.str();
}