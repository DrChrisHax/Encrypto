#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

#pragma once 

uint32_t keyToNum(const std::string &key);
std::string encrypt(const std::string &text, const uint32_t key);
std::string decrypt(const std::string &text, const uint32_t key);
char swapBits(char c);
std::string stringToHex(const std::string& input);
std::string hexToString(const std::string& hexInput);



