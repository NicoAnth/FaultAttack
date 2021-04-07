#include "FaultAttack.h"
#include "BitsManips.h"
#include <bitset>

int main(int argc , char** argv) {

    std::string correctCypher = "144FED14635AFD89";
    std::string FaultCypher1 = "164EED50635AFD8D";

    //Hexa into string bin
    std::string binC = hex_str_to_bin_str(correctCypher);
    std::string binF = hex_str_to_bin_str(FaultCypher1);
    std::cout << binC << std:: endl;

    //IPFunction
    std::string ipBin = ipDES(binC);
    std::string ipBinF = ipDES(binF);
    std::cout << ipBin << std::endl;

    //SplitIntoLandR
    std::string L16;
    std::string R16;
    splitIntoLandR(R16,L16,ipBin);
    std::string L16F;
    std::string R16F;
    splitIntoLandR(R16F,L16F,ipBinF);
    std::cout << R16 << ", "<< L16 << std::endl;

    //Expansion
    std::string ER15 = expansion(L16);
    std::string ER15F = expansion(L16F);
    std::cout << ER15 << std::endl;
    std::cout << ER15F << std::endl;

    //Get the difference between the input of the S-boxes from the normal execution and the output of the S-boxes from the faulty execution
    std::string diffIn = XOR(ER15,ER15F,48);

    //Get the difference between the output of the S-boxes from the normal execution and the output of the S-boxes from the faulty execution
    std::string diffOut = reversePermutation(XOR(R16,R16F,32));
    std::cout << XOR(R16,R16F,32) << std::endl;
    std::cout << diffOut << std::endl;

    //Reverse permutation

    return 0;
}
