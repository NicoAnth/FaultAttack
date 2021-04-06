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

    //Swap bits
    std::string sbBin = swapBits(bin,62,2);
    std::cout << sbBin << std::endl;

    return 0;
}
