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
    
    int k=0;
    vector<vector<int>> col2(3, vector<int>(52,0));
    while(std::getline(f,line)){
        //std::istringstream ss(line);
        int i=0;
        int n = line.size();

        vector<int> col(52,0);
        

        for(int j=0; j<n; ++j){
            int x = line[j];
            if(x >= 'a'){
                x = x -'a';
            } else {
                x = x -'A'+26;
            }
            col2[k][x]++;
        }

        for(;i<n/2; ++i){
            int x = line[i];
            if(x >= 'a'){
                x = x -'a';
            } else {
                x = x -'A'+26;
            }
            col[x] += 1;

        }
        
        for(;i<n; ++i){
            int x = line[i];
            if(x >= 'a'){
                x = x-'a';
            } else {
                x = x - 'A'+26;
            }

            if(col[x] > 0){
                score = score+ 1+x;
                i=n;
            }
            
        }
        
        k++;
        if(k==3){
            k=0;
            for(int j=0; j<52; ++j){
                if(col2[0][j]>0 && col2[1][j]>0 && col2[2][j]> 0){
                    score2 += j+1;
                    break;
                }
            }
            col2 = vector<vector<int>>(3, vector<int>(52,0));
        }
    }
    
    

    std::cout << score << std::endl;
    std::cout << score2 << std::endl;

    std::cout << std::endl << "Execution Complete"<< std::endl;
    return 0;
    }
