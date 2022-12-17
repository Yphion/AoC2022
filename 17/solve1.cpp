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
    
    vector<vector<bool>> S(9, vector<bool>(1, true));
    int rocks = 0;

    vector<pair<int,int>> A;
    bool alive = false;
    int type = 0;



    std::getline(f,line);
    int time = 0;
    int top = 0;

    while(rocks < 2022){
        if(!alive) {

            if(type == 0){ // -
                type++;
                while(S[0].size() < top + 5){
                    for(int i=1; i<8; ++i){
                        S[i].push_back(false);
                    }
                    S[0].push_back(true);
                    S[8].push_back(true);
                }

                A.push_back(pair<int,int>(3, top+4));
                A.push_back(pair<int,int>(4, top+4));
                A.push_back(pair<int,int>(5, top+4));
                A.push_back(pair<int,int>(6, top+4));

            } else if (type==1) { //cross
                type++;
                while(S[0].size() < top + 7){
                    for(int i=1; i<8; ++i){
                        S[i].push_back(false);
                    }
                    S[0].push_back(true);
                    S[8].push_back(true);
                }

                A.push_back(pair<int,int>(4, top+6));
                A.push_back(pair<int,int>(5, top+5));
                A.push_back(pair<int,int>(4, top+5));
                A.push_back(pair<int,int>(3, top+5));
                A.push_back(pair<int,int>(4, top+4));

            } else if (type==2) { // L
                type++;
                while(S[0].size() < top + 7){
                    for(int i=1; i<8; ++i){
                        S[i].push_back(false);
                    }
                    S[0].push_back(true);
                    S[8].push_back(true);
                }

                A.push_back(pair<int,int>(5, top+6));
                A.push_back(pair<int,int>(5, top+5));
                A.push_back(pair<int,int>(3, top+4));
                A.push_back(pair<int,int>(4, top+4));
                A.push_back(pair<int,int>(5, top+4));

            } else if(type==3){ // I
                type++;
                while(S[0].size() < top + 8){
                    for(int i=1; i<8; ++i){
                        S[i].push_back(false);
                    }
                    S[0].push_back(true);
                    S[8].push_back(true);
                }
                A.push_back(pair<int,int>(3, top+4));
                A.push_back(pair<int,int>(3, top+5));
                A.push_back(pair<int,int>(3, top+6));
                A.push_back(pair<int,int>(3, top+7));

            } else { //square
                type = 0;
                while(S[0].size() < top + 6){
                    for(int i=1; i<8; ++i){
                        S[i].push_back(false);
                    }
                    S[0].push_back(true);
                    S[8].push_back(true);
                }
                A.push_back(pair<int,int>(3, top+4));
                A.push_back(pair<int,int>(3, top+5));
                A.push_back(pair<int,int>(4, top+4));
                A.push_back(pair<int,int>(4, top+5));

            }

            alive = true;
        }

        int dir = 1;
        if(line[time] == '<'){
            dir = -1;
        }
        time = (time + 1) % line.size();

        vector<pair<int,int>> B;

        bool wall = false;

        for(pair<int,int> p : A){
            if(S[p.first+dir][p.second]){
                wall = true;
                break;
            }
        }

        if(not wall){
            for(pair<int,int> &p : A){
                p.first += dir;
            }
        }

        wall = false;
        for(pair<int,int> p : A){
            if(S[p.first][p.second-1]){
                wall = true;
                break;
            }
        }

        if(wall){
            alive = false;
            for(pair<int,int> p : A){
                S[p.first][p.second] = true;
                if(p.second > top){
                    top = p.second;
                }
            }
            A.clear();
            rocks++;

        } else {
            for(pair<int,int> &p : A){
                p.second--;
            }
        }

    }

    score = top;

    std::cout << score << std::endl;

    std::cout << std::endl << "Execution Complete"<< std::endl;
    return 0;
    }
