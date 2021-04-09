#include "FaultAttack.h"

//Apply IP function on the given string
std::string ipDES(std::string cipher){
    
    std::string ipx ="";
    int ipTab [64] = {58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7};
    int i;
    for (i=0;i<64;i++){
        ipx+=cipher[ipTab[i]-1];
    } 
    return ipx;
}

//Split the given string to half L and R values 
void splitIntoLandR(std::string& L, std::string& R, std::string cipher){

    L = cipher.substr(0,32);
    R = cipher.substr(32,32);
}

//Apply DES function expansion on the given string
std::string expansion(std::string cipher){
    std::string exp="";
    int expTab[48]{32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1};
    int i;
    for(i=0;i<48;i++){
        exp+=cipher[expTab[i]-1];
    }
    return exp;
}

// Return P^-1 on the given string
std::string reversePermutation(std::string cipher){
    std::string revPerm="";
    int permTab[32]{9, 17, 23, 31,
                      13, 28, 2, 18,
                      24, 16, 30, 6,
                      26, 20, 10, 1,
                      8, 14, 25, 3,
                      4, 29, 11, 19,
                      32, 12, 22, 7,
                      5, 27, 15, 21};
    int i;
    for(i=0;i<32;i++){
        revPerm+= cipher[permTab[i]-1];
    }
    return revPerm;
}

//Split S-boxes input into 8 to get the 8 S-boxes input
std::vector<std::string> siBoxIn(std::string cipher){

    std::vector<std::string> siBoxVec;
    for(int i=0;i<48;i+=6){
        siBoxVec.push_back(cipher.substr(i,6));
    }
    return siBoxVec;
}

//Split S-boxes output into 8 to get the 8 S-boxes output
std::vector<std::string> siBoxOut(std::string cipher){

    std::vector<std::string> siBoxVec;
    for(int i=0;i<32;i+=4){
        siBoxVec.push_back(cipher.substr(i,4));
    }
    return siBoxVec;
}

//Return the output of the given cipher passed into the 8 S-boxes. If ibox is specified, return the cipher passed in the ith box.
//Note that 0 is the first box
std::string sBox(std::string cipher, int ibox){

    std::string sBoxOut = "";
    
    if (ibox != 8 && cipher.length() != 6){
        return "Error :Cipher length must be 6";
    }
    if (ibox == 8 && cipher.length() != 48){
        return "Error :Cipher length must be 48";
    }

    int substition_boxes[8][4][16]=  
	{{ 
        14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7, 
        0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8, 
        4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0, 
        15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 
    }, 
    { 
        15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10, 
        3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5, 
        0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15, 
        13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 
    }, 
    { 
        10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8, 
        13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1, 
        13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7, 
        1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 
    }, 
    { 
        7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15, 
        13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9, 
        10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4, 
        3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 
    }, 
    { 
        2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9, 
        14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6, 
        4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14, 
        11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 
    }, 
    { 
        12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11, 
        10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8, 
        9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6, 
        4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 
    }, 
    { 
        4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1, 
        13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6, 
        1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2, 
        6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 
    }, 
    { 
        13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7, 
        1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2, 
        7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8, 
        2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 
    }};

    if (ibox==8){

        for(int i=0;i<8; i++){ 
            // Finding row and column indices to lookup the
            // substituition box
            std::string row1= cipher.substr(i*6,1) + cipher.substr(i*6 + 5,1);
            int row = convertBinaryToDecimal(row1);
            std::string col1 = cipher.substr(i*6 + 1,1) + cipher.substr(i*6 + 2,1) + cipher.substr(i*6 + 3,1) + cipher.substr(i*6 + 4,1);;
            int col = convertBinaryToDecimal(col1);
            sBoxOut.append(convertDecimalToBinary(substition_boxes[i][row][col]));
        }
    }
    else {
            std::string row1= cipher.substr(0,1) + cipher.substr(5,1);
            int row = convertBinaryToDecimal(row1);
            std::string col1 = cipher.substr(1,1) + cipher.substr(2,1) + cipher.substr(3,1) + cipher.substr(4,1);;
            int col = convertBinaryToDecimal(col1);
            sBoxOut.append(convertDecimalToBinary(substition_boxes[ibox][row][col]));
    }

    return sBoxOut;
}



//Build the Difference Distribution Table of DES
std::vector<std::vector<std::vector<int> > > siDDT (){
    
    // Initialize a vector of size 8*64*16 with the value 0
    std::vector<std::vector<std::vector<int> > > table (8,std::vector<std::vector<int> >(64,std::vector <int>(16,0))); // the table[In][Out], In is the XOR of the in-going pair, Out is the resulting XOR, the table returns the number of occurences

    // Initialize the tables:
    for(int i=0;i<8;i++){
        // this makes us go through all the possible value of p1
        for(int p1 = 0;p1<64;p1++) 
        {
            // this makes us go through all the possible value of p2
            for(int p2 = 0;p2<64;p2++)
            {
                std::string p1s = convertDecimalToBinary(p1,6); //doit valoir toujours 6 bits
                std::string p2s = convertDecimalToBinary(p2,6);
                std::string XOR_IN = XOR(p1s,p2s,6);
                std::string XOR_OUT = XOR(sBox(p1s,i),sBox(p2s,i),4);
                
                table[i][convertBinaryToDecimal(XOR_IN)][convertBinaryToDecimal(XOR_OUT)]++;
            }
        } 
    }
    return table;
}

//Return every pair given a XOR.
std::vector<std::pair<std::string,std::string>> generatePairs(std::string xorValue){

    std::vector<std::pair<std::string,std::string>> pairs;
    int xori = convertBinaryToDecimal(xorValue);

    for(int i=0;i<64;i++){
        for(int j=0;j<64;j++){
            if((i^j) == xori){
                pairs.push_back(std::make_pair(convertDecimalToBinary(i,6),convertDecimalToBinary(j,6)));
            }
        }
    }
    return pairs;
}

//Return the number of occurrence of a key given a vector of possible keys
//keyOccurence[key number]= "key string", occurrence
std::vector<std::pair<std::string,int>> keyOccurrence(std::vector<std::string> keysVec){
    
    std::vector<std::string> keysVecCopy = keysVec;

    std::sort(keysVecCopy.begin(), keysVecCopy.end());
    keysVecCopy.erase(std::unique(keysVecCopy.begin(), keysVecCopy.end()), keysVecCopy.end());
    
    std::vector<std::pair<std::string,int>> keyOc(keysVecCopy.size(),std::make_pair("",0));

    for(int i=0;i != (int)keyOc.size();i++){
        keyOc[i].first = keysVecCopy[i];
    }
    for(int i=0;i != (int)keysVec.size();i++){
        keyOc[i].second = count(keysVec.begin(),keysVec.end(),keysVecCopy[i]);
    }

    return keyOc;
}

bool compare(std::pair<std::string, int> p1, std::pair<std::string, int> p2) {
    return p1.second<p2.second;
}

//Return the key K16
/* std::vector<std::string> findK16(std::vector<std::pair<std::string,int>> kOccurrence){
    
    std::vector<std::string> key;
    for(int i=0;i<)
    max_element(kOccurrence[i].begin(), kOccurrence[i].end(), compare)


} */