#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

int main(){
    std::ifstream f("input.txt");
    std::string line;
    
    std::cout << "Running Program"<< std::endl << std::endl;
    
    long q = 0;
    std::vector<long> qlist;
    long max = 0;
    while(std::getline(f,line)){
        std::istringstream ss(line);
        long f;
        if(!(ss >> f)){
            qlist.push_back(q);
            if (q > max){
                max = q;
            }
            q = 0;
        } else {
            ss >> f;
            q += f;
        }
    }

    qlist.push_back(q);
    if (q > max){
        max = q;
    }

    std::sort(qlist.begin(), qlist.end());
    int n = qlist.size();
    std::cout << max << std::endl;
    std::cout << qlist[n-1] + qlist[n-2] + qlist[n-3] << std::endl;

    std::cout << std::endl << "Execution Complete"<< std::endl;
    return 0;
    }
