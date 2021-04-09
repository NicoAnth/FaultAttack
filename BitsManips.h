#ifndef BITSMANIPS__H_
#define BITSMANIPS__H_

#include <sstream>
#include <bitset>
#include <string>
#include <bits/stdc++.h>

const char* hexCharToBin(char c);
std::string hexStrToBinStr(const std::string& hex);
void createMap(std::unordered_map<std::string, char> *um);
std::string convertBinToHex(std::string bin);
void swapBits (std::string& bin, int p1, int p2);
std::string XOR (std::string a, std::string b, int n);
std::string Xor(std::string a, std::string b);
std::string convertDecimalToBinary(int decimal, long unsigned int i=4);
int convertBinaryToDecimal(std::string binary);
std::string shift_left_once(std::string key_chunk);
std::string shift_left_twice(std::string key_chunk);

#endif