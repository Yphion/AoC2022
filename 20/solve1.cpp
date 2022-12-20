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


    long long score = 0;

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

    for(int i=0; i<n; ++i){
        int pos = V[i].second;
        long long val = V[i].first;

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

    score = V[Q[(V[zero].second+1000) % n]].first + V[Q[(V[zero].second+2000) % n]].first + V[Q[(V[zero].second+3000) % n]].first;

    std::cout << score << std::endl;

    std::cout << std::endl << "Execution Complete"<< std::endl;
    return 0;
    }#include <iostream>
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


    long long score = 0;

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

    for(int i=0; i<n; ++i){
        int pos = V[i].second;
        long long val = V[i].first;

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

    score = V[Q[(V[zero].second+1000) % n]].first + V[Q[(V[zero].second+2000) % n]].first + V[Q[(V[zero].second+3000) % n]].first;

    std::cout << score << std::endl;

    std::cout << std::endl << "Execution Complete"<< std::endl;
    return 0;
    }
