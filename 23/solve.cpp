#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <limits.h>

#define long long long

using namespace std;

typedef pair<int,int> P;

struct Elf {
    int id; 
    int x;
    int y;

    Elf(int id, int x, int y) : id(id), x(x), y(y) {}
};

int main(){
    std::ifstream f("input.txt");
    std::string line;
    
    std::cout << "Running Program"<< std::endl << std::endl;


    long score = 0;
    long score2 = 0;

    vector<Elf> E;
    map<P, int> pmap;


    int index = 0;
    int row = 0;
    while(std::getline(f,line)){

        std::istringstream ss(line);
        for(int i=0; i<line.size(); ++i){
            if(line[i] == '#'){
                pmap[P(i, row)] = index;
                E.push_back(Elf(index++, i, row));
            }
        }
        row++;
    }
    
    map<P, int> nmap;

    int moves = 1;
    int dir = 0;
    int rounds = 0;
    while(moves > 0){
        if(rounds == 10){
            int xmax = INT_MIN;
            int xmin = INT_MAX;
            int ymax = INT_MIN;
            int ymin = INT_MAX;

            for(Elf &e : E){
                xmax = max(xmax, e.x);
                xmin = min(xmin, e.x);
                ymax = max(ymax, e.y);
                ymin = min(ymin, e.y);
            }

            score = (xmax-xmin+1)*(ymax-ymin+1)-E.size();
        }
        rounds++;
        moves = 0;

        for(Elf &e : E){
            if(pmap.count(P(e.x+1,e.y)) == 0 && pmap.count(P(e.x+1,e.y+1)) == 0 && pmap.count(P(e.x,e.y+1)) == 0 && pmap.count(P(e.x-1,e.y+1)) == 0 && pmap.count(P(e.x-1,e.y)) == 0 && pmap.count(P(e.x-1,e.y-1)) == 0 && pmap.count(P(e.x,e.y-1)) == 0 && pmap.count(P(e.x+1,e.y-1)) == 0){
                continue;
            }
            for(int i=0; i<4; ++i){
                int d = (dir + i) % 4;
                if(d == 0){ //n
                    if(pmap.count(P(e.x-1,e.y-1)) == 0 && pmap.count(P(e.x,e.y-1)) == 0 && pmap.count(P(e.x+1,e.y-1)) == 0){
                        if(nmap.count(P(e.x, e.y-1))){
                            nmap[P(e.x, e.y-1)] = -1;
                        } else {
                            nmap[P(e.x, e.y-1)] = e.id;
                        }
                        break;
                    }
                } else if (d==1){ //s
                    if(pmap.count(P(e.x-1,e.y+1)) == 0 && pmap.count(P(e.x,e.y+1)) == 0 && pmap.count(P(e.x+1,e.y+1)) == 0){
                        if(nmap.count(P(e.x, e.y+1))){
                            nmap[P(e.x, e.y+1)] = -1;
                        } else {
                            nmap[P(e.x, e.y+1)] = e.id;
                        }
                        break;
                    }
                } else if (d==2){ //w
                    if(pmap.count(P(e.x-1,e.y-1)) == 0 && pmap.count(P(e.x-1,e.y)) == 0 && pmap.count(P(e.x-1,e.y+1)) == 0){
                        if(nmap.count(P(e.x-1, e.y))){
                            nmap[P(e.x-1, e.y)] = -1;
                        } else {
                            nmap[P(e.x-1, e.y)] = e.id;
                        }
                        break;
                    }
                } else { //e
                    if(pmap.count(P(e.x+1,e.y-1)) == 0 && pmap.count(P(e.x+1,e.y)) == 0 && pmap.count(P(e.x+1,e.y+1)) == 0){
                        if(nmap.count(P(e.x+1, e.y))){
                            nmap[P(e.x+1, e.y)] = -1;
                        } else {
                            nmap[P(e.x+1, e.y)] = e.id;
                        }
                        break;
                    }
                }
            }
        }

        pmap.clear();

        for(auto &x : nmap){
            if(x.second != -1){
                moves++;
                Elf &e = E[x.second];
                e.x = x.first.first;
                e.y = x.first.second;
            }
        }

        nmap.clear();

        for(Elf &e : E){
            pmap[P(e.x,e.y)] = e.id;
        }

        dir = (dir+1)%4;
    }

    score2 = rounds;

    std::cout << score << std::endl;
    std::cout << score2 << std::endl;

    std::cout << std::endl << "Execution Complete"<< std::endl;
    return 0;
    }
