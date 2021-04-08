#include "FaultAttack.h"
#include "BitsManips.h"
#include <bitset>

void faultAttackf(){

    std::string correctCypher = "144FED14635AFD89";
    std::vector<std::string> FaultCyphers = {"164EED50635AFD8D","144DED50635BFD89","145FEF50635AFD89","151FE956735AFD89","151FED54715BFD89","150FE9147358FD89","154FED14735AFF89","140FE915234EFD8B",
    "1C4FE915335AFD89","1447ED15234AFD89","144FE515235EFD89","544FFD1C234AFD89","544FFD156B4AFD89","544FED146312FD88","544FFD14631AF589","144FFD14671AED80","744FFD14671AFCC8","146FED14675AFC89",
    "144FCD14635AECC9","004FEC34635AEC89","104FEC14435AECC9","004FAD14637AFD89","104FAC14635ADD89","044FAC14635AB9A9","804FED14625ABD89","14CFED04625AF989","144F6D14635AB989","144AED84635AB989",
    "144EED04E25AFD8D","144BED1463DAFD8D","144FED14635A7D9D","144AED54635BFD0D"};

    for(int j=0;j<1;j++){
        
    //Hexa into string bin
    std::string binC = hexStrToBinStr(correctCypher);
    std::string binF = hexStrToBinStr(FaultCyphers[j]);

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
    

    //Expansion     
    std::string ER15 = expansion(L16);
    std::string ER15F = expansion(L16F);
    std::cout << "ER15 :" << ER15 << std::endl;
    std::cout << "ER15F :" << ER15F << std::endl;
    //Get the difference between the input of the S-boxes from the normal execution and the output of the S-boxes from the faulty execution
    std::string diffIn = XOR(ER15,ER15F,48);
    std::vector<std::string> sBoxInput = siBoxIn(diffIn);
    //std::cout << "diff In Value :" << diffIn << std::endl;
    /*std::cout << "diff In Value hexa:" << convertBinToHex(diffIn) << std::endl;*/
    std::cout << "S-box 1 input :" << sBoxInput[0] << std::endl;


    //Get the difference between the output of the S-boxes from the normal execution and the output of the S-boxes from the faulty execution
    std::string diffOut = reversePermutation(XOR(R16,R16F,32));
    std::vector<std::string> sBoxOutput = siBoxOut(diffOut);
    /* std::cout << "diff Out Value :" << diffOut << std::endl;
    std::cout << "S-box 8 output :" << sBoxOutput[0] << std::endl; */

    //Generate the 8 Difference Distribution Table
    std::vector<std::vector<std::vector<int>>> diffDistributionTable = siDDT();

    //Get Difference Distribution Table value for our ciphers
    std::vector<int> value;
    std::cout << "Difference Distribution Table Value :" ;
    for(int i=0;i<8;i++){
        value.push_back(diffDistributionTable[i][convertBinaryToDecimal(sBoxInput[i])][convertBinaryToDecimal(sBoxOutput[i])]);
        std::cout << value[i] << ", ";
    }
    for(int i=0;i<64;i++){
        //std::cout << generatePairs(sBoxInput[0])[i].first << " ,"<< generatePairs(sBoxInput[0])[i].second << std::endl;
        std::string entreePossible = XOR(sBox(generatePairs(sBoxInput[0])[i].first,0),sBox(generatePairs(sBoxInput[0])[i].second,0),4);
        if(entreePossible == sBoxOutput[0]){
        std::cout << XOR(generatePairs(sBoxInput[0])[i].first,ER15,6) << std::endl;
        }
    }
    }

}


int main(int argc , char** argv) {

    faultAttackf();
    return 0;
}
