#include "BitsManips.h"

const char* hexCharToBin(char c)
{
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
    return "conversion error";
}
//Convert hex to binary
std::string hexStrToBinStr(const std::string& hex)
{
    std::string bin;
    for(unsigned i = 0; i != hex.length(); ++i)
       bin += hexCharToBin(hex[i]);
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
     
    int len_left = t != -1 ? t : l;
     
    for (int i = 1; i <= (4 - len_left % 4) % 4; i++)
        bin = '0' + bin;
      
    if (t != -1)   
    {
        
        int len_right = l - len_left - 1;
         
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
// XOR two binary values, n is the size of the given strings.
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
//Convert decimal value to binary value. If i is specified, value's will be i bits.
std::string convertDecimalToBinary(int decimal, long unsigned int i)
{
	std::string binary;
    while(decimal != 0) {
		binary = (decimal % 2 == 0 ? "0" : "1") + binary; 
		decimal = decimal/2;
	}
	while(binary.length() < i){
		binary = "0" + binary;
	}
    return binary;
}

// Function to convert a number in binary to decimal
int convertBinaryToDecimal(std::string binary)
{
    int decimal = 0;
	int counter = 0;
	int size = binary.length();
	for(int i = size-1; i >= 0; i--)
	{
    	if(binary[i] == '1'){
        	decimal += pow(2, counter);
    	}
    counter++;
	}
	return decimal;
}