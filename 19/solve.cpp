#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <deque>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<VVI> VVVI;

typedef tuple<int,int,int,int> I4;
typedef tuple<I4, I4, int> S; //rob, res, t 

struct Blueprint{
    int c00;
    int c10;
    int c20;
    int c21;
    int c30;
    int c32;
};

long solve(Blueprint bp, int t){

    S init = S(I4(1,0,0,0), I4(0,0,0,0), t);

    deque<S> Q;
    Q.push_back(init);
    
    set<S> v;
    v.insert(init);
    int opt = 0;
    
    while(!Q.empty()){
        S s = Q.front();
        Q.pop_front();
        

        I4 &rob = get<0>(s);
        I4 &res = get<1>(s);
        int tt = get<2>(s);
        I4 nres = I4(get<0>(res)+get<0>(rob),get<1>(res)+get<1>(rob),get<2>(res)+get<2>(rob),get<3>(res)+get<3>(rob));

        opt = max(opt, get<3>(res));
        if(get<3>(res) < opt) continue;

        if(tt == 0) continue;

        if(get<2>(res) >= bp.c32 && get<0>(res) >= bp.c30) { //build geode robot
            I4 nrob(get<0>(rob), get<1>(rob), get<2>(rob), get<3>(rob)+1);
            get<0>(nres) -= bp.c30;
            get<2>(nres) -= bp.c32;
            S n(nrob, nres, tt-1);
            if(v.count(n) == 0) {
                v.insert(n);
                Q.push_back(n);
            }   
        } else if (get<1>(res) >= bp.c21 && get<0>(res) >= bp.c20){ //build obsidian robot
            I4 nrob(get<0>(rob), get<1>(rob), get<2>(rob)+1, get<3>(rob));
            get<0>(nres) -= bp.c20;
            get<1>(nres) -= bp.c21;
            S n(nrob, nres, tt-1);
            if(v.count(n) == 0) {
                v.insert(n);
                Q.push_back(n);
            } 
        } else {
            S l(rob, nres, tt-1);
            if(v.count(l) == 0) {
                v.insert(l);
                Q.push_back(l);
            } 

            if(get<0>(res) >= bp.c10){
                 I4 nrob(get<0>(rob), get<1>(rob)+1, get<2>(rob), get<3>(rob));
                 I4 nnres = nres;
                 get<0>(nnres) -= bp.c10;
                 S n(nrob, nnres, tt-1);
                 if(v.count(n) == 0) {
                    v.insert(n);
                    Q.push_back(n);
                 } 
            }

            if(get<0>(res) >= bp.c00){
                 I4 nrob(get<0>(rob)+1, get<1>(rob), get<2>(rob), get<3>(rob));
                 I4 nnres = nres;
                 get<0>(nnres) -= bp.c00;
                 S n(nrob, nnres, tt-1);
                 if(v.count(n) == 0) {
                    v.insert(n);
                    Q.push_back(n);
                 } 
            }

        }
    }

    return opt;
}

int main(){
    std::ifstream f("input.txt");
    std::string line;
    
    std::cout << "Running Program"<< std::endl << std::endl;


    long score = 0;
    long score2 = 1;

    vector<Blueprint> BP;
    
    while(std::getline(f,line)){

        if(line.size() == 0) continue;

        Blueprint bp;
        int q;
        sscanf(line.c_str(),"Blueprint %i: Each ore robot costs %i ore. Each clay robot costs %i ore. Each obsidian robot costs %i ore and %i clay. Each geode robot costs %i ore and %i obsidian.",&q,&bp.c00,&bp.c10,&bp.c20,&bp.c21,&bp.c30,&bp.c32);
        BP.push_back(bp);
    }

    for(int i=0; i<BP.size(); ++i){
        int val = solve(BP[i], 24);
        cout << i << ": " << val << endl;
        score += (i+1)*val;
    }

    for(int i=0; i<3; ++i){
        int val = solve(BP[i], 32);
        score2 *=val;
    }

    std::cout << score << std::endl;
    std::cout << score2 << std::endl;

    std::cout << std::endl << "Execution Complete"<< std::endl;
    return 0;
    }
