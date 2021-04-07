#include <sstream>
#include <bitset>
#include <string>
#include <bits/stdc++.h>

const char* hex_char_to_bin(char c);
std::string hex_str_to_bin_str(const std::string& hex);
void createMap(std::unordered_map<std::string, char> *um);
std::string convertBinToHex(std::string bin);
void swapBits (std::string& bin, int p1, int p2);
std::string XOR (std::string a, std::string b, int n);
