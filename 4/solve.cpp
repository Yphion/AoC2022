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
        
        for(int i=0; i<line.size(); ++i){
            if(line[i] == '-' || line[i]==','){
                line[i] = ' ';
            }
        }

        std::istringstream ss(line);
        int a, b, c, d;
        ss >> a >> b >> c >> d;

    	if ((a <= c && b >= d) || (c <= a && d >= b)){
            score++;
        }

        if(!((b < c) || (d < a))){
            score2++;
        }

    }
    
    

    std::cout << score << std::endl;
    std::cout << score2 << std::endl;

    std::cout << std::endl << "Execution Complete"<< std::endl;
    return 0;
    }
