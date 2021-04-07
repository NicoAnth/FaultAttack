#include "FaultAttack.h"
#include "BitsManips.h"
#include <bitset>

int main(int argc , char** argv) {

    std::string correctCypher = "144FED14635AFD89";
    std::string FaultCypher1 = "164EED50635AFD8D";

    //Hexa into string bin
    std::string binC = hexStrToBinStr(correctCypher);
    std::string binF = hexStrToBinStr(FaultCypher1);
    /* std::cout << binC << std:: endl; */

    //IPFunction
    std::string ipBin = ipDES(binC);
    std::string ipBinF = ipDES(binF);
    /* std::cout << ipBin << std::endl; */

    //SplitIntoLandR
    std::string L16;
    std::string R16;
    splitIntoLandR(R16,L16,ipBin);
    std::string L16F;
    std::string R16F;
    splitIntoLandR(R16F,L16F,ipBinF);
    /* std::cout << R16 << ", "<< L16 << std::endl; */

    //Expansion
    std::string ER15 = expansion(L16);
    std::string ER15F = expansion(L16F);
    /* std::cout << ER15 << std::endl;
    std::cout << ER15F << std::endl; */

    //Get the difference between the input of the S-boxes from the normal execution and the output of the S-boxes from the faulty execution
    std::string diffIn = XOR(ER15,ER15F,48);
    std::vector<std::string> sBoxInput = siBoxIn(diffIn);
    std::cout << "diff In Value :" << diffIn << std::endl;
    /* std::cout << "diff In Value hexa:" << convertBinToHex(diffIn) << std::endl;
    std::cout << "S-box 8 input :" << sBoxInput[7] << std::endl; */


    //Get the difference between the output of the S-boxes from the normal execution and the output of the S-boxes from the faulty execution
    std::string diffOut = reversePermutation(XOR(R16,R16F,32));
    std::vector<std::string> sBoxOutput = siBoxOut(diffOut);
    std::cout << "diff Out Value :" << diffOut << std::endl;
    /* std::cout << "diff Out Value hexa:" << convertBinToHex(diffOut) << std::endl;
    std::cout << "S-box 8 output :" << sBoxOutput[7] << std::endl; */

    //Generate the 8 Difference Distribution Table
    std::vector<std::vector<std::vector<int>>> diffDistributionTable = siDDT();
    std::cout << "Difference Distribution Table of S1 :" << diffDistributionTable[0][32][5] << std::endl;

    return 0;
}
