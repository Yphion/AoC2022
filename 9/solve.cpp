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
    
    vector<pair<char, int>> moves;
    
    int maxl = 0;
    int maxr = 0;
    int maxu = 0;
    int maxd = 0;
    
    int x = 0;
    int y = 0;
    
    while(std::getline(f,line)){

        // int a, b, c, d;
        // sscanf(line.c_str(),"%i-%i,%i-%i",&a,&b,&c,&d);

        std::istringstream ss(line);
        char c; int steps;
        ss >> c >> steps;
        moves.push_back(pair<char,int>(c, steps));


        if(c == 'R'){
            x += steps;
            if(x > maxr){
                maxr = x;
            }
        } else if(c== 'L'){
            x -= steps;
            if(-x > maxl){
                maxl = -x;
            }
        } else if(c=='U'){
            y += steps;
            if(y > maxu){
                maxu = y;
            }
        } else if (c=='D'){
            y -= steps;
            if(-y > maxd){
                maxd = -y;
            }
        }
        
    }
    
    int n = moves.size();
    
    vector<vector<bool>> visited(maxl+1+maxr, vector<bool>(maxu + 1 + maxd, false));
    vector<vector<bool>> visited2(maxl+1+maxr, vector<bool>(maxu + 1 + maxd, false));
    
    int hx = maxl;
    int hy = maxd;

    int tx = maxl;
    int ty = maxd;

    vector<pair<int,int>> pos(10, pair<int,int>(maxl, maxd));

    visited[tx][ty] = true;
    visited2[tx][ty] = true;

    for(int i=0; i<n; ++i){
        char c = moves[i].first;
        int steps = moves[i].second;
        
        while(steps-- > 0){
            if(c == 'R'){
                pos[0].first++;
            } else if(c=='L'){
                pos[0].first--;
            } else if(c=='U'){
                pos[0].second++;
            } else if (c=='D'){
                pos[0].second--;
            }

            for(int i=1; i<10; ++i){
                hx = pos[i-1].first;
                hy = pos[i-1].second;

                tx = pos[i].first;
                ty = pos[i].second;

                int xdiff = abs(hx-tx);
                int ydiff = abs(hy-ty);

                if(xdiff == ydiff){
                    if(xdiff > 1){
                        if(hx > tx){
                            tx = hx-1;
                        } else {
                            tx = hx+1;
                        }

                        if(hy > ty){
                            ty = hy-1;
                        } else {
                            ty = hy+1;
                        }
                    }
                } else if (xdiff > ydiff){
                    if(xdiff > 1){
                        if(hx > tx){
                            tx = hx-1;
                        } else {
                            tx = hx+1;
                        }
                        ty = hy;
                    }
                } else {
                    if(ydiff > 1){
                        if(hy > ty){
                            ty = hy-1;
                        } else {
                            ty = hy+1;
                        }
                        tx = hx;
                    }
                }

                pos[i] = pair<int,int>(tx,ty);
            }
            visited[pos[1].first][pos[1].second] = true;
            visited2[tx][ty] = true;
        }
    }

    for(int i = 0; i<visited.size(); ++i){
        for(int j = 0; j< visited[0].size(); ++j){
            if(visited[i][j]){
                score++;
            } 
        }
    }
    for(int i = 0; i<visited2.size(); ++i){
        for(int j = 0; j< visited2[0].size(); ++j){
            if(visited2[i][j]){
                score2++;
            } 
        }
    }

    std::cout << score << std::endl;
    std::cout << score2 << std::endl;

    std::cout << std::endl << "Execution Complete"<< std::endl;
    return 0;
    }
