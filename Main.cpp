#include "FaultAttack.h"
#include "BitsManips.h"
#include "DES.h"
#include <bitset>



int main(int argc , char** argv) {

    //Compute a Fault Attack on DES in order to find K16
    std::vector<std::string> K16 = faultAttackf();
    std::string K16s;

    //Print K16
    std::cout <<"K16 :";
    for (auto i = K16.begin(); i != K16.end(); ++i){
        std::cout << *i ;
        K16s += *i;
    }
    std::cout<<std::endl;
    
    //find and print K
    findDESKey(K16s);

    return 0;
}
