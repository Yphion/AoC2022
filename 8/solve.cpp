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
    
    vector<vector<int>> grid;
    
    
    int n = 0;

    while(std::getline(f,line)){
        grid.push_back(vector<int>());
        for(int i=0; i<line.size(); i++){
            grid[n].push_back(line[i]-'0');
        }
        n++;
    }

    int m = grid[0].size();
    vector<vector<bool>> visible(n, vector<bool>(m, false));

    int qmax;
    for(int i=0; i<n; ++i){ //left
        qmax = -1;
        for(int j=0; j<m; ++j){
            if(grid[i][j] > qmax){
                qmax = grid[i][j];
                visible[i][j] = true;
            }
        }
    }
    
    for(int i=0; i<n; ++i){//right
        qmax = -1;
        for(int j=m-1; j>=0; --j){
            if(grid[i][j] > qmax){
                qmax = grid[i][j];
                visible[i][j] = true;
            }
        }
    } 

    for(int j=0; j<m; ++j){//top
        qmax = -1;
        for(int i=0; i<n; ++i){
            if(grid[i][j] > qmax){
                qmax = grid[i][j];
                visible[i][j] = true;
            }
        }
    } 

    for(int j=0; j<m; ++j){//bottom
        qmax = -1;
        for(int i=n-1; i>=0; --i){
            if(grid[i][j] > qmax){
                qmax = grid[i][j];
                visible[i][j] = true;
            }
        }
    } 

    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            if(visible[i][j]) {
                score++;
            } else {
            }
        }
    }

    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            long tscore = 1;
            int h = grid[i][j];
            int a = i-1;
            int cnt = 0;
            while(a >= 0){ //left
                cnt ++;
                if(grid[a][j] < h){
                    a--;
                } else {
                    break;
                }
            }
            tscore *= cnt;

            cnt = 0;
            a = i+1;
            while(a < n){ //right
                cnt ++;
                if(grid[a][j] < h){
                    a++;
                } else {
                    break;
                }
            }
            tscore *= cnt;

            cnt = 0;
            a = j+1;
            while(a < m){ //bottom
                cnt ++;
                if(grid[i][a] < h){
                    a++;
                } else {
                    break;
                }
            }
            tscore *= cnt;

            cnt = 0;
            a = j-1;
            while(a >= 0){ //top
                cnt ++;
                if(grid[i][a] < h){
                    a--;
                } else {
                    break;
                }
            }
            tscore *= cnt;

            if(tscore > score2){
                score2 = tscore;
            }
        }

    }

    std::cout << score << std::endl;
    std::cout << score2 << std::endl;

    std::cout << std::endl << "Execution Complete"<< std::endl;
    return 0;
    }
