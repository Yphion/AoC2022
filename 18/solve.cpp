#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>


using namespace std;

typedef tuple<int,int,int> Coord;
typedef tuple<Coord, Coord, int> Cube;

int dfs(map<Coord, vector<Coord>> &Adj, Coord pos, set<Coord> &visited, vector<vector<vector<bool>>> &grid){
    int count = 0;
    for(Coord x : Adj[pos]){
        if(visited.count(x) > 0){

        } else {
            
            int i = get<0>(x);
            int j = get<1>(x);
            int k = get<2>(x);

            if(i > 0 && grid[i-1][j][k]){
                count++;
            }

            if(i < 21 && grid[i+1][j][k]){
                count++;
            }

            if(j > 0 && grid[i][j-1][k]){
                count++;
            }
            
            if(j < 21 && grid[i][j+1][k]){
                count++;
            }

            if(k > 0 && grid[i][j][k-1]){
                count++;
            }
            
            if(k < 21 && grid[i][j][k+1]){
                count++;
            }

            visited.insert(x);
            count += dfs(Adj, x, visited, grid);
        }
    }

    return count;
}

int main(){
    std::ifstream f("input.txt");
    std::string line;
    
    std::cout << "Running Program"<< std::endl << std::endl;


    long long score = 0;
    long long score2 = 0;
    
    long long cubes = 0;
    set<Cube> S;
    set<Coord> Cubes;

    vector<vector<vector<bool>>> grid(22, vector<vector<bool>>(22, vector<bool>(22, false)));
    
    while(std::getline(f,line)){

        for(int i=0; i<line.size(); ++i){
            if(line[i]==','){
                line[i] = ' ';
            }
        }

        std::istringstream ss(line);
        
        int a, b, c;
        ss >> a >> b >> c;
        
        Coord v1 = Coord(a,b,c);
        Coord v2 = Coord(a+1, b, c);
        Coord v3 = Coord(a+1, b+1, c);
        Coord v4 = Coord(a, b+1, c);

        Coord v5 = Coord(a, b, c+1);
        Coord v6 = Coord(a+1, b, c+1);

        S.insert(Cube(v1, v2, 0)); //floor
        S.insert(Cube(v1, v2, 1)); //front
        S.insert(Cube(v2, v3, 1)); //right
        S.insert(Cube(v1, v4, 1)); //left
        S.insert(Cube(v4, v3, 1)); //back
        S.insert(Cube(v5, v6, 0)); //top

        grid[a][b][c] = true;
        Cubes.insert(Coord(a,b,c));

        cubes++;

    }

    long long inter = 6*Cubes.size()-S.size();
    score = 6*Cubes.size()-2*inter;

    map<Coord, vector<Coord>> Adj;
    Adj[Coord(-1,-1,-1)] = vector<Coord>();
    int fullout = 0;
    for(int i=0; i<22; ++i){
        for(int j=0; j<22; ++j){
            for(int k=0; k<22; ++k){

                if(grid[i][j][k] == 1) {
                    if(i==0 || i ==21){
                        fullout++;
                    }

                    if(j==0 || j==21){
                        fullout++;
                    }

                    if(k==0 || k==21){
                        fullout++;
                    }
                    continue;
                }
                Coord x = Coord(i,j,k);
                
                Adj[x] = vector<Coord>();

                if(i > 0 && !grid[i-1][j][k]){
                    Adj[x].push_back(Coord(i-1, j, k));
                }

                if (i<21 && !grid[i+1][j][k]){
                    Adj[x].push_back(Coord(i+1, j, k));
                }

                if(j > 0 && !grid[i][j-1][k]){
                    Adj[x].push_back(Coord(i, j-1, k));
                }

                if(j<21 && !grid[i][j+1][k]){
                    Adj[x].push_back(Coord(i, j+1, k));
                }

                if(k>0 && !grid[i][j][k-1]){
                    Adj[x].push_back(Coord(i, j, k-1));
                }

                if(k<21 && !grid[i][j][k+1]){
                    Adj[x].push_back(Coord(i, j, k+1));
                }

                if(i == 0 || j== 0 || k == 0 || i == 21 || j == 21 || k == 21){
                    Adj[x].push_back(Coord(-1,-1,-1));
                    Adj[Coord(-1,-1,-1)].push_back(x);
                }
            }
        }
    }

    set<Coord> visited;
    visited.insert(Coord(-1,-1,-1));
    int out = dfs(Adj, Coord(-1,-1,-1), visited, grid);
    score2 = fullout + out;

    std::cout << score << std::endl;
    std::cout << score2 << std::endl;

    std::cout << std::endl << "Execution Complete"<< std::endl;
    return 0;
    }
