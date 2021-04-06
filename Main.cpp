#include "FaultAttack.h"
#include "BitsManips.h"

int main(int argc , char** argv) {

    std::string s = "64706BDA3B79FDD0";
    std::cout << hex_str_to_bin_str(s) << std:: endl;
    std::string hexa = hex_str_to_bin_str(s);
    std::cout << convertBinToHex(hexa)<< std::endl;
    return 0;
}
