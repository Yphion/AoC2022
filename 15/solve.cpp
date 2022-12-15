#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <CGAL/Gmpz.h>

using namespace std;

int main(){
    std::ifstream f("input.txt");
    std::string line;
    
    std::cout << "Running Program"<< std::endl << std::endl;


    long score = 0;
    long score2 = 0;
    
    

    set<int> row;
    set<int> bcs;

    vector<tuple<long,long,long>> Pos;    

    while(std::getline(f,line)){

        for(int i=0; i<line.size(); ++i){
            if(line[i]=='=' || line[i]==',' || line[i] == ':'){
                line[i] = ' ';
            }
        }

        std::istringstream ss(line);
        string s;
        long x,y,bx,by;
        ss >> s >> s >> s >> x >> s >> y >> s >> s >> s >> s >> s >> bx >> s >> by;
        
        int dist = abs(x-bx)+abs(y-by);

        long dy = abs(2000000-y);

        Pos.push_back(tuple<long,long,long>(x,y,dist));

        if(by == 2000000){
            bcs.insert(bx);
        }

        for(int i=x-dist+dy; i<=x+dist-dy; ++i){
                row.insert(i);
        }
    }


    score = (row.size()-bcs.size());

    std::cout << score << std::endl;


    long off = 4000000;

    for(int i=0; i<= off; ++i){
        for(int j=0; j<off; ++j){
            bool found = true;
            for(auto t : Pos){
                long dist = abs(get<0>(t)-i) + abs(get<1>(t)-j);
                long alt = get<2>(t);
                if(dist <= alt){
                    j += alt-dist;
                    found = false;
                    break;
                }
                
            }
            if(found){
                cout << i << " " << j << endl;     
                cout << (CGAL::Gmpz(i)*4000000+j) << endl;          
                i = off+1;
                break;
            }
        }
    }

    std::cout << std::endl << "Execution Complete"<< std::endl;
    return 0;
    }
