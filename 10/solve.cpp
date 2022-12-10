#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>


using namespace std;



int main(){
    std::ifstream f("input.txt");
    std::string line;
    
    std::cout << "Running Program"<< std::endl << std::endl;


    long score = 0;
    long score2 = 0;
    
    int time = 1;
    int sval = 1;

    while(std::getline(f,line)){

        std::istringstream ss(line);
        
        string op;
        int val;
        ss >> op;
        if(op == "noop"){
            time++;
            
            if((time+20) % 40 == 0){
                score += sval*time;
            }

            if(abs(((time-1)%40)-sval) < 2){
                cout << "#";
            } else {
                cout << ".";
            }
            if((time-1)%40 == 0){
                cout << endl;
            }
        } else {
            ss >> val;
            time++;
            if((time+20) % 40 == 0){
                score += sval*time;
            }

            if(abs(((time-1)%40)-sval) < 2){
                cout << "#";
            } else {
                cout << ".";
            }
            if((time-1)%40 == 0){
                cout << endl;
            }

            time++;
            sval += val;

            if((time+20) % 40 == 0){
                score += sval*time;
            }

            if(abs(((time-1)%40)-sval) < 2){
                cout << "#";
            } else {
                cout << ".";
            }
            if((time-1)%40 == 0){
                cout << endl;
            }
        }
        
    }
    
    

    std::cout << score << std::endl;

    std::cout << std::endl << "Execution Complete"<< std::endl;
    return 0;
    }
