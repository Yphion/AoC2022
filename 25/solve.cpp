#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <boost/lexical_cast/lexical_cast_old.hpp>

#define long long long

using namespace std;

string toSNAFU(long x){
    long y = x;
    long mults = 1;
    long mult = 5;
    long val = 0;
    string res = "";
    while(y != 0){
        long off = y % 5;
        y /= 5;
        if (off == 4){
            val += -1*mults;
            res = "-"+res;
            y += 1;
        } else if(off == 3){
            res = "="+res;
            val += -2*mults;
            y += 1;
        } else {
            val += off;
            res = boost::lexical_cast<std::string>(off) + res;
        }

        mults *= 5;
        mult *= 5;
    }

    return res;

}

int main(){
    std::ifstream f("input.txt");
    std::string line;
    
    std::cout << "Running Program"<< std::endl << std::endl;

    long sum1 = 0;

    while(std::getline(f,line)){

        long mult = 1;
        long sum = 0;

        for(int i=line.size()-1; i>=0; --i){
            char c = line[i];
            int v = c-'0';
            if(c == '-'){
                v = -1;
            } else if(c == '='){
                v = -2;
            }
            sum += v*mult;
            mult *= 5;
        }

        sum1 += sum;
        
        
    }
    
    std::cout << toSNAFU(sum1) << std::endl;

    std::cout << std::endl << "Execution Complete"<< std::endl;
    return 0;
    }
