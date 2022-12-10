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

    int part = 0;
    vector<vector<char>> stacks;
    vector<vector<char>> stacks2;

    while(std::getline(f,line)){
        if(part == 0){

            if(line[1] == '1') {

                part = 1;
            } else {
                int j = 0;
                for(int i=1; i<line.size(); i+=4, j++){
                    if(stacks.size() <= j){
                        stacks.push_back(vector<char>(0,0));
                        stacks2.push_back(vector<char>(0,0));
                    }
                    if (line[i] != ' '){
                        stacks[j].push_back(line[i]);
                    }
                }
            }
        }

        if(part == 1){
            part = 3;

            for(int i=0; i<stacks.size(); ++i){
                vector<char> tmp;
                for(int j=0; j<stacks[i].size(); ++j){
                    tmp.push_back(stacks[i][j]);
                }
                for(int j=0; j<tmp.size(); ++j){
                    stacks[i][tmp.size()-1-j] = tmp[j];
                    stacks2[i].push_back(tmp[tmp.size()-1-j]);
                }
            }
            continue;
        } 

        if(part == 3){
            if(line.size() == 0) continue;
            int a, b, c;
            sscanf(line.c_str(),"move %i from %i to %i",&a,&b,&c);

            for(int i=stacks2[b-1].size()-a; i<stacks2[b-1].size(); ++i){
                stacks2[c-1].push_back(stacks2[b-1][i]);
            }

            while(a>0){
                a--;
                
                stacks[c-1].push_back(stacks[b-1].back());
                stacks[b-1].pop_back();
                stacks2[b-1].pop_back();
            }
        }
    }
    
    
    for(int i=0; i<stacks.size(); ++i){
        cout << stacks[i].back();
    }
    cout << endl;

    for(int i=0; i<stacks.size(); ++i){
        cout << stacks2[i].back();
    }
    cout << endl;

    std::cout << std::endl << "Execution Complete"<< std::endl;
    return 0;
    }
