#include "BitsManips.h"

const char* hex_char_to_bin(char c)
{
    // TODO handle default / error
    switch(toupper(c))
    {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
    }
    return 0;
}

std::string hex_str_to_bin_str(const std::string& hex)
{
    std::string bin;
    for(unsigned i = 0; i != hex.length(); ++i)
       bin += hex_char_to_bin(hex[i]);
    return bin;
}

void createMap(std::unordered_map<std::string, char> *um)
{
    (*um)["0000"] = '0';
    (*um)["0001"] = '1';
    (*um)["0010"] = '2';
    (*um)["0011"] = '3';
    (*um)["0100"] = '4';
    (*um)["0101"] = '5';
    (*um)["0110"] = '6';
    (*um)["0111"] = '7';
    (*um)["1000"] = '8';
    (*um)["1001"] = '9';
    (*um)["1010"] = 'A';
    (*um)["1011"] = 'B';
    (*um)["1100"] = 'C';
    (*um)["1101"] = 'D';
    (*um)["1110"] = 'E';
    (*um)["1111"] = 'F';
}
 
// function to find hexadecimal
// equivalent of binary
std::string convertBinToHex(std::string bin)
{
    int l = bin.size();
    int t = bin.find_first_of('.');
     
    // length of string before '.'
    int len_left = t != -1 ? t : l;
     
    // add min 0's in the beginning to make
    // left substring length divisible by 4
    for (int i = 1; i <= (4 - len_left % 4) % 4; i++)
        bin = '0' + bin;
     
    // if decimal point exists   
    if (t != -1)   
    {
        // length of std::string after '.'
        int len_right = l - len_left - 1;
         
        // add min 0's in the end to make right
        // substd::string length divisible by 4
        for (int i = 1; i <= (4 - len_right % 4) % 4; i++)
            bin = bin + '0';
    }
     
    // create map between binary and its
    // equivalent hex code
    std::unordered_map<std::string, char> bin_hex_map;
    createMap(&bin_hex_map);
     
    int i = 0;
    std::string hex = "";
     
    while (1)
    {
        // one by one extract from left, substring
        // of size 4 and add its hex code
        hex += bin_hex_map[bin.substr(i, 4)];
        i += 4;
        if ((long unsigned int) i == bin.size())
            break;
             
        // if '.' is encountered add it
        // to result
        if (bin.at(i) == '.')   
        {
            hex += '.';
            i++;
        }
    }
     
    // required hexadecimal number
    return hex;   
}

//Swap position of two bits. 
void swapBits (std::string& bin, int p1, int p2){

    int tmp1,tmp2;
    tmp1 = bin[p1];
    tmp2 = bin[p2];
    bin[p1] = tmp2;
    bin[p2] = tmp1;

}

std::string XOR (std::string a, std::string b, int n){
    
    std::string ans = "";
      
    for (int i = 0; i < n; i++)
    {
        if (a[i] == b[i])
            ans += "0";
        else
            ans += "1";
    }
    return ans;
}
