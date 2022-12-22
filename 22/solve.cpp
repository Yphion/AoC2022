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

int main(){
    std::ifstream f("input.txt");
    std::string line;
    
    std::cout << "Running Program"<< std::endl << std::endl;


    long score = 0;
    long score2 = 0;


    int m = 150;

    vector<vector<int>> F;

    vector<int> P;
    
    int xi = -1;
    int yi = 0;

    while(std::getline(f,line)){

        int num = 0;
        bool nm = false;

        if (line.size() > 150 || line.size() == 15){
            for(int i=0; i<line.size(); ++i){
                if ('0' <= line[i] && line[i] <= '9'){
                    num = 10*num + line[i] - '0';
                    nm = true;
                } else {
                    if(nm){
                        P.push_back(num);
                        nm = false;
                        num = 0;
                    }
                    if(line[i] == 'L') {
                        P.push_back(-1);
                    } else if (line[i] == 'R'){
                        P.push_back(1);
                    } else {
                        cout << "Unexpected input." << endl;
                    }

                }
            }
            P.push_back(num);

            break;
        }
        std::istringstream ss(line);
        vector<int> f(m, 0);
        
        for(int i=0; i<line.size(); ++i){
            if(line[i] == '.'){
                if(xi==-1) xi = i;
                f[i] = 1; 
            } else if (line[i] == '#'){
                f[i] = 2;
            }
        }

        F.push_back(f);
    }
    

    int n = F.size();
    map<tuple<int,int,int>, int> wmap;

    for(int i=0; i<n; ++i){ //r
        int first = -1;
        for(int j=0; j<m; ++j){
            if(F[i][j] != 0){
                if (first == -1){
                    first = j;
                }
            } else {
                if (first > -1){
                    wmap[tuple<int,int,int>(j,i,0)] = first;
                    first = -2;
                    break;
                }
            }
        }
        if (first != -2){
            wmap[tuple<int,int,int>(m,i,0)] = first;
        }
    }

    for(int j=0; j<m; ++j){ //d
        int first = -1;
        for(int i=0; i<n; ++i){
            if(F[i][j] != 0){
                if (first == -1){
                    first = i;
                }
            } else {
                if (first > -1){
                    wmap[tuple<int,int,int>(j,i,1)] = first;
                    first = -2;
                    break;
                }
            }
        }
        if (first != -2){
            wmap[tuple<int,int,int>(j,n,1)] = first;
        }
    }

    for(int i=0; i<n; ++i){ //l
        int first = -1;
        for(int j=m-1; j>=0; --j){
            if(F[i][j] != 0){
                if (first == -1){
                    first = j;
                }
            } else {
                if (first > -1){
                    wmap[tuple<int,int,int>(j,i,2)] = first;
                    first = -2;
                    break;
                }
            }
        }
        if (first != -2){
            wmap[tuple<int,int,int>(-1,i,2)] = first;
            first = -2;
        }
    }

    for(int j=0; j<m; ++j){ //u
        int first = -1;
        for(int i=n-1; i>=0; --i){
            if(F[i][j] != 0){
                if (first == -1){
                    first = i;
                }
            } else {
                if (first > -1){
                    wmap[tuple<int,int,int>(j,i,3)] = first;
                    first = -2;
                    break;
                }
            }
        }
        if (first != -2){
            wmap[tuple<int,int,int>(j,-1,3)] = first;
        }
    }
    int x = xi;
    int y = yi;
    int d = 0;

    for(int i=0; i<P.size(); ++i){
        if (i%2 == 0){
            
            int steps = P[i];

            while(steps-- > 0){
                if(d == 0){
                    int xold = x;
                    x++;
                    if (x >= m || F[y][x] == 0){
                        x = wmap[tuple<int,int,int>(x,y,d)];
                    }
                    if(F[y][x] == 2){
                        x = xold;
                        break;
                    }
                } else if (d==1){
                    int yold = y;
                    y++;
                    if (y >= n || F[y][x] == 0){
                        y = wmap[tuple<int,int,int>(x,y,d)];
                    }
                    if(F[y][x] == 2){
                        y = yold;
                        break;
                    }
                } else if (d == 2){
                    int xold = x;
                    x--;
                    if (x < 0 || F[y][x] == 0){
                        x = wmap[tuple<int,int,int>(x,y,d)];
                    }
                    if(F[y][x] == 2){
                        x = xold;
                        break;
                    }
                } else if (d==3){
                    int yold = y;
                    y--;
                    if (y < 0 || F[y][x] == 0){
                        y = wmap[tuple<int,int,int>(x,y,d)];
                    }
                    if(F[y][x] == 2){
                        y = yold;
                        break;
                    }
                }
            }

        } else {
            d = (d+P[i]+4) % 4;
        }
    }

    score = 1000*(y+1) + 4*(x+1) + d;

    x = xi;
    y = yi;
    d = 0;

    for(int i=0; i<P.size(); ++i){
        if (i%2 == 0){
            
            int steps = P[i];

            while(steps-- > 0){
                if(d == 0){
                    int xold = x;
                    int yold = y;
                    int dold = d;
                    x++;
                    if (x >= m || F[y][x] == 0){
                        if(y < 50){
                            x = 99;
                            y = 149-y;
                            d = 2;
                        } else if(y < 100){
                            x = 100 + (y - 50);
                            y = 49;
                            d = 3;
                        } else if (y < 150){
                            y = 149-y;
                            x = 149;
                            d = 2;
                        } else {
                            x = 50 + y - 150;
                            y = 149;
                            d = 3;
                        }
                    }
                    if(F[y][x] == 2){
                        x = xold;
                        y = yold;
                        d = dold;
                        break;
                    }
                } else if (d==1){
                    int xold = x;
                    int yold = y;
                    int dold = d;
                    y++;
                    if (y >= n || F[y][x] == 0){
                        if(x < 50){
                            x = x + 100;
                            y = 0;
                            d = 1;
                        } else if(x < 100){
                            y = 150 + x - 50;
                            x = 49;
                            d = 2;
                        } else {
                            y = 50 + x - 100;
                            x = 99;
                            d = 2;
                        }
                    }
                    if(F[y][x] == 2){
                        x = xold;
                        y = yold;
                        d = dold;
                        break;
                    }
                } else if (d == 2){
                    int xold = x;
                    int yold = y;
                    int dold = d;
                    x--;
                    if (x < 0 || F[y][x] == 0){
                        if(y < 50){
                            y = 149-y;
                            x = 0;
                            d = 0;
                        } else if(y < 100){
                            x = y - 50;
                            y = 100;
                            d = 1;
                        } else if(y < 150){
                            y = 149-y;
                            x = 50;
                            d = 0;
                        } else {
                            x = 50 + y - 150;
                            y = 0;
                            d = 1;
                        }
                    }
                    if(F[y][x] == 2){
                        x = xold;
                        y = yold;
                        d = dold;
                        break;
                    }
                } else if (d==3){
                    int xold = x;
                    int yold = y;
                    int dold = d;
                    y--;
                    if (y < 0 || F[y][x] == 0){
                        if (x < 50){
                            y = 50 + x;
                            x = 50;
                            d = 0;
                        } else if(x < 100){
                            y = 150 + x - 50;
                            x = 0;
                            d = 0;
                        } else {
                            x = x - 100;
                            y = 199;
                            d = 3;
                        }
                    }
                    if(F[y][x] == 2){
                        x = xold;
                        y = yold;
                        d = dold;
                        break;
                    }
                }
            }

        } else {
            d = (d+P[i]+4) % 4;
        }
    }

    score2 = 1000*(y+1) + 4*(x+1) + d;

    std::cout << score << std::endl;
    std::cout << score2 << std::endl;

    std::cout << std::endl << "Execution Complete"<< std::endl;
    return 0;
    }
