#include "FaultAttack.h"
#include "BitsManips.h"
#include <bitset>

std::vector<std::string> faultAttackf(){
    std::string correctCypher = "144FED14635AFD89";
    std::vector<std::string> FaultCyphers = {"164EED50635AFD8D","144DED50635BFD89","145FEF50635AFD89","151FE956735AFD89","151FED54715BFD89","150FE9147358FD89","154FED14735AFF89","140FE915234EFD8B",
    "1C4FE915335AFD89","1447ED15234AFD89","144FE515235EFD89","544FFD1C234AFD89","544FFD156B4AFD89","544FED146312FD88","544FFD14631AF589","144FFD14671AED80","744FFD14671AFCC8","146FED14675AFC89",
    "144FCD14635AECC9","004FEC34635AEC89","104FEC14435AECC9","004FAD14637AFD89","104FAC14635ADD89","044FAC14635AB9A9","804FED14625ABD89","14CFED04625AF989","144F6D14635AB989","144AED84635AB989",
    "144EED04E25AFD8D","144BED1463DAFD8D","144FED14635A7D9D","144AED54635BFD0D"};

    //Generate the 8 Difference Distribution Table, diffDistributionTable[S-Box][x][y]
    std::vector<std::vector<std::vector<int>>> diffDistributionTable = siDDT();

    //2D Vector of Difference Distribution Table output, ddtoValue[FaultCipherNumber][S-box]
    std::vector<std::vector<int>> ddtoValue(31);

    //2D Vector of possibles keys, possibleKeys[S-Box][key Number]
    std::vector<std::vector<std::string>> possibleKeys(8);

    //Hexa into string bin
    std::string binC = hexStrToBinStr(correctCypher);

    //IPFunction
    std::string ipBin = ipDES(binC);

    //SplitIntoLandR
    std::string L16;
    std::string R16;
    splitIntoLandR(R16,L16,ipBin);

    //Expansion     
    std::string ER15 = expansion(L16);

    //Iterate over every fault ciphers
    for(int i=0;i<31;i++){

    //Hexa into string bin
    std::string binF = hexStrToBinStr(FaultCyphers[i]);

    //IPFunction
    std::string ipBinF = ipDES(binF);
    /* std::cout << ipBin << std::endl; */

    //SplitIntoLandR
    std::string L16F;
    std::string R16F;
    splitIntoLandR(R16F,L16F,ipBinF);
    
    //Expansion
    std::string ER15F = expansion(L16F);
    /* std::cout << "ER15 :" << ER15 << std::endl;
    std::cout << "ER15F :" << ER15F << std::endl;
 */
    //Get the difference between the input of the S-boxes from the normal execution and the output of the S-boxes from the faulty execution
    std::string diffIn = XOR(ER15,ER15F,48);
    std::vector<std::string> sBoxInput = siBoxIn(diffIn);
    //std::cout << "diff In Value :" << diffIn << std::endl;
    /*std::cout << "diff In Value hexa:" << convertBinToHex(diffIn) << std::endl;*/
    /* std::cout << "S-box 1 input :" << sBoxInput[0] << std::endl; */


    //Get the difference between the output of the S-boxes from the normal execution and the output of the S-boxes from the faulty execution
    std::string diffOut = reversePermutation(XOR(R16,R16F,32));
    std::vector<std::string> sBoxOutput = siBoxOut(diffOut);
    /* std::cout << "diff Out Value :" << diffOut << std::endl;
    std::cout << "S-box 8 output :" << sBoxOutput[0] << std::endl; */

    //Get Difference Distribution Table value for our ciphers
    for(int j=0;j<8;j++){
        ddtoValue[i].push_back(diffDistributionTable[j][convertBinaryToDecimal(sBoxInput[j])][convertBinaryToDecimal(sBoxOutput[j])]);
    }
    //Iterate over the 8 S-Boxes <---- La clé est parfaitement générée pour la première s-box
    for (int j=0;j<8;j++){
        //If (Si,I⊕,Si,O⊕) has a number of (Si,I,Si,I*) possible couple != 64 and >0 
        if( (ddtoValue[i][j] != 0) && (ddtoValue[i][j] != 64)){          
            
            //Get every existing couple which XOR result is S_i,I⊕
            std::vector<std::pair<std::string,std::string>> PairsVec = generatePairs(sBoxInput[j]);

            //For every existing couple
            for(int k=0;k<64;k++){

                //XOR S_i(S_i,I) and S_i(S_i,I)* and stock the value if it's equal to S_i,O⊕
                std::string candidateKeyXor = XOR(sBox(PairsVec[k].first,j),sBox(PairsVec[k].second,j),4); 
                    if(candidateKeyXor == sBoxOutput[j]){
                        possibleKeys[j].push_back(XOR(PairsVec[k].first,ER15.substr(j*6,6),6));
                    }
            }
        }
    }
    }
    std::vector<std::string> K16;
    //Iterate over the 8 S-boxes
    for(int i=0; i<8;i++){

        //Return the possible keys associated with their occurrence.
        std::vector<std::pair<std::string,int>> kO = keyOccurrence(possibleKeys[i]); // <------ Ca fonctionne
        //std::cout<<"Key "<< i << " :"<<kO[i].first<< " occurrence: "<< kO[i].second << std::endl;

        //pick the max of the keyOccurrence Vector
        const auto maxOccurrence = max_element(kO.begin(), kO.end(), [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });
        K16.push_back(maxOccurrence->first);
        /* std::cout<<"Max occurrence s-box "<< i << " :"<<maxOccurrence->second << ", "; */
    }
    return K16;
}


int main(int argc , char** argv) {

    std::vector<std::string> K16 = faultAttackf();
    
    //Print K16
    std::cout <<"K16 :";
    for (auto i = K16.begin(); i != K16.end(); ++i){
        std::cout << *i ;
    }
    std::cout<<std::endl;
    
    return 0;
}
