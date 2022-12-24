#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

#define long long long

using namespace std;

typedef tuple<int,int,int> Blz;
typedef pair<int,int> Pos;

int main(){
    std::ifstream f("input.txt");
    std::string line;
    
    std::cout << "Running Program"<< std::endl << std::endl;

    long score = 0;
    long score2 = 0;
    
    int source = 0;
    int target = 0;

    int n = 0;
    int m = 0;

    vector<Blz> B;

    while(std::getline(f,line)){

        std::istringstream ss(line);
        if(line[2] == '#'){
            m = line.size()-2;
            target = line.size()-3;
            continue;
        }

        for(int i=1; i<line.size()-1; ++i){
            if(line[i] == '>'){
                B.push_back(Blz(n, i-1, 0));
            } else if (line[i] == 'v'){
                B.push_back(Blz(n, i-1, 1));
            } else if (line[i] == '<'){
                B.push_back(Blz(n, i-1, 2));
            } else if (line[i] == '^'){
                B.push_back(Blz(n, i-1, 3));
            }
        }
        
        n++;
    }

    set<Pos> Q;
    

    set<Pos> newQ;
    newQ.insert(Pos(-1, source));
    vector<vector<bool>> A;

    int round = 0;
    int running = true;

    bool down = true;
    int count = 0;

    while(running){
        Q = newQ;
        newQ.clear();
        if(Q.count(Pos(-1, source))){
            newQ.insert(Pos(-1, source));
        } else if (Q.count(Pos(n, target))){
            newQ.insert(Pos(n, target));
        }

        A = vector<vector<bool>>(n, vector<bool>(m, true));
        for(Blz &b : B){
            switch(get<2>(b)) {
                case 0:
                    get<1>(b) = (get<1>(b)+1) % m;
                    break;
                case 1:
                    get<0>(b) = (get<0>(b)+1) % n;
                    break;
                case 2:
                    get<1>(b) = (get<1>(b)-1+m) % m;
                    break;
                case 3:
                    get<0>(b) = (get<0>(b)-1+n) % n;
                    break;
                default:
                    cout << "Error: Unexpected direction" << endl;
            }
            A[get<0>(b)][get<1>(b)] = false;
        }

        for (const Pos &p : Q){
            if(down && p.first == -1){
                if(A[0][0]){
                    newQ.insert(Pos(0,0));
                }
                continue;
            } 

            if(!down && p.first == n){
                if(A[n-1][m-1]){
                    newQ.insert(Pos(n-1,m-1));
                }
                continue;
            }

            if(!down && p.first == 0 && p.second == 0){
                down = true;
                newQ.clear();
                newQ.insert(Pos(-1, source));
                break;
            }

            if(down && p.first == n-1 && p.second == target){
                if(count == 0){
                    score = round+1;
                }
                down = false;
                count++;
                
                if(count == 2){
                    running = false;
                    score2 = round+1;
                }
                newQ.clear();
                newQ.insert(Pos(n, target));
                break;
            }

            int x = p.first;
            int y = p.second;

            if(A[x][y]){
                newQ.insert(Pos(x,y));
            }

            if(x > 0 && A[x-1][y]){
                newQ.insert(Pos(x-1,y));
            }

            if(x < n-1 && A[x+1][y]){
                newQ.insert(Pos(x+1,y));
            }

            if(y > 0 && A[x][y-1]){
                newQ.insert(Pos(x,y-1));
            }

            if(y < m-1 && A[x][y+1]){
                newQ.insert(Pos(x,y+1));
            }

        }
        round++;
    }

    std::cout << score << std::endl;
    std::cout << score2 << std::endl;

    std::cout << std::endl << "Execution Complete"<< std::endl;
    return 0;
    }
