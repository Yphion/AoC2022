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
    
    vector<vector<bool>> A(1000, vector<bool>(1000, false));   

    while(std::getline(f,line)){

        for(int i=0; i<line.size(); ++i){
            if(line[i]==','){
                line[i] = ' ';
            }
        }

        std::istringstream ss(line);
        
        int a, b;
        string s;
        bool first = true;

        int x, y;
        while(ss >> a >> b){
            if(first){
                first = false;
                x = a;
                y = b;
                A[x][y] = true;
            } else {
                A[a][b] = true;
                if (x==a){
                    while(y > b){
                        y--;
                        A[x][y] = true;
                    }

                    while(y < b){
                        y++;
                        A[x][y] = true;
                    }
                } else {
                    while(x > a){
                        x--;
                        A[x][y] = true;
                    }
                    while(x < a){
                        x++;
                        A[x][y] = true;
                    }
                }
                x = a;
                y = b;
            }

            ss >> s;
        }

    }

    int spawn = 0;

    int units = 0;
    int step = 0;
    bool alive = true;
    while(alive){
        int x = 500;
        int y = 0;
        units++;

        while(true){

            if(y == 999){
                alive = false;
                break;
            }

            if(!A[x][y+1]){
                y++;
            } else if(!A[x-1][y+1]){
                y++;
                x--;
            } else if(!A[x+1][y+1]){
                y++;
                x++;
            } else {
                A[x][y] = true;
                break;
            }
            step++;
        }
    }

    score = units - 1;

    std::cout << score << std::endl;

    std::cout << std::endl << "Execution Complete"<< std::endl;
    return 0;
    }
