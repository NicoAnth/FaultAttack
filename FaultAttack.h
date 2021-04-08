#ifndef FAULTATTACK__H_
#define FAULTATTACK__H_

#include <iostream>
#include "BitsManips.h"

std::string ipDES(std::string chiffre);
void splitIntoLandR(std::string& L, std::string& R, std::string cipher );
std::string expansion(std::string cipher);
std::string reversePermutation(std::string cipher);
std::vector<std::string> siBoxIn(std::string cipher);
std::vector<std::string> siBoxOut(std::string cipher);
std::string sBox(std::string cipher, int ibox=8);
std::vector<std::vector<std::vector<int> > > siDDT ();
std::vector<std::pair<std::string,std::string>> generatePairs(std::string xorValue);

#endif