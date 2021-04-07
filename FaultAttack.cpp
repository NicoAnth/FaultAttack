#include "FaultAttack.h"

std::string ipDES(std::string cipher){
    
    std::string ipx ="";
    int ipTab [64] = {58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7};
    int i;
    for (i=0;i<64;i++){
        ipx+=cipher[ipTab[i]-1];
    } 
    return ipx;
}   

void splitIntoLandR(std::string& L, std::string& R, std::string cipher){

    L = cipher.substr(0,32);
    R = cipher.substr(32,32);
}

std::string expansion(std::string cipher){
    std::string exp="";
    int expTab[48]{32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1};
    int i;
    for(i=0;i<48;i++){
        exp += cipher[expTab[i]-1];
    }
    return exp;
}

std::string reversePermutation(std::string cipher){
    std::string revPerm=cipher;
    int permTab[32]{16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25};
    int i;
    for(i=0;i<32;i++){
        swapBits(revPerm,i,permTab[i]-1);
    }
    return revPerm;
}