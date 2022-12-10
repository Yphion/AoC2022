#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    std::ifstream f("input.txt");
    std::string line;
    
    std::cout << "Running Program"<< std::endl << std::endl;


    long score = 0;
    long score2 = 0;

    while(std::getline(f,line)){
        std::istringstream ss(line);

        char lt, lt2;
        ss >> lt >> lt2;
        
        lt -= 'A';
        lt2 -= 'X';

        score += (4+lt2-lt)%3*3 + lt2+1;

        score2 += lt2*3 + (2+lt+lt2)%3 + 1;
    }

    std::cout << score << std::endl;
    std::cout << score2 << std::endl;

    std::cout << std::endl << "Execution Complete"<< std::endl;
    return 0;
    }
