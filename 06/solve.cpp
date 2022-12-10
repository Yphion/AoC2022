#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main(){
    std::ifstream f("input.txt");
    std::string line;
    
    std::cout << "Running Program"<< std::endl << std::endl;

    long score = 0;
    long score2 = 0;

    while(std::getline(f,line)){

        for(int i=3; i<line.size(); ++i){
            set<char> s;
            set<char> s2;
            for(int j=0; j<4; ++j){
                s.insert(line[i-j]);
            }
            if(i >= 13){
                for(int j=0; j<14; ++j){
                    s2.insert(line[i-j]);
                }
            }
            if(s.size() == 4 && score == 0){
                score = i+1;
            }

            if(s2.size() == 14){
                score2 = i+1;
                break;
            }
        }
        
    }

    std::cout << score << std::endl;
    std::cout << score2 << std::endl;

    std::cout << std::endl << "Execution Complete"<< std::endl;
    return 0;
    }
