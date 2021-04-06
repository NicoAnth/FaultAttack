#include "FaultAttack.h"
#include "BitsManips.h"
#include <bitset>

int main(int argc , char** argv) {

    std::string s = "64706BDA3B79FDD0";

    //Hexa into string bin
    std::string bin = hex_str_to_bin_str(s);
    std::cout << bin << std:: endl;

    //Bin into string Hexa
    std::string hexa = convertBinToHex(bin);
    std::cout << hexa << std::endl;

    //IPFunction
    std::string ipBin = ipDES(bin);
    std::cout << ipBin << std::endl;

    //SplitIntoLandR
    std::string L16;
    std::string R16;
    splitIntoLandR(R16,L16,ipBin);
    std::cout << R16 << ", "<< L16 << std::endl;
    return 0;
}
