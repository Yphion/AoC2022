#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <CGAL/Gmpz.h>

typedef CGAL::Gmpz Z;

using namespace std;

int main(){
    std::ifstream f("input.txt");
    std::string line;
    
    std::cout << "Running Program"<< std::endl << std::endl;

    long long score = 0;
    
    vector<long long> O;
    vector<pair<long long,int>> V;
    
    vector<int> Q;

    int index = 0;
    int zero = 0;
    while(std::getline(f,line)){
        std::istringstream ss(line);
        int a;
        ss >> a;

        if(a == 0){
            zero = index;
        }

        Q.push_back(index);
        V.push_back(pair<int,int>(a, index++));
        
    }
    
    int n = V.size();
    long long mul = 811589153LL;

    for(int i=0; i<n; ++i){
        O.push_back(V[i].first * mul);
        V[i].first = (V[i].first * mul) % (n*(n-1));
    }

    for(int k=0; k<10; ++k){
        for(int i=0; i<n; ++i){
            long long val = V[i].first;

            if(val > 0){
                long long shift = val / (n-1);
                for(int j=0; j<n; ++j){
                    V[j].second = ((V[j].second - shift) % n + n) % n;
                    Q[V[j].second] = j;
                }
                val = val % (n-1);
            } else {
                long long shift = (-val) / (n-1);
                for(int j=0; j<n; ++j){
                    V[j].second = (V[j].second + shift) % n;
                    Q[V[j].second] = j;
                }
                val = val % (n-1);
            }

            int pos = V[i].second;

            for(long long j=0; j<val; ++j){
                int npos = (pos+1)%n;
                V[Q[pos]].second = npos;
                V[Q[npos]].second = pos;
                swap(Q[pos], Q[npos]);
                pos = npos;
            }

            for(long long j=0; j>val; --j){
                int npos = pos - 1;
                if(npos == -1) npos = n-1;
                V[Q[pos]].second = npos;
                V[Q[npos]].second = pos;
                swap(Q[pos], Q[npos]);
                pos = npos;
            }
        }
    }

    score = O[Q[(V[zero].second+1000) % n]] + O[Q[(V[zero].second+2000) % n]] + O[Q[(V[zero].second+3000) % n]];

    std::cout << score << std::endl;

    std::cout << std::endl << "Execution Complete"<< std::endl;
    return 0;
    }
