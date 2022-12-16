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
    
    map<string,int> s2i;
    s2i["AA"] = 0;
    int index = 1;

    vector<vector<int>> Adj(1, vector<int>());
    vector<int> value(1,0);

    int fcnt = 0;

    while(std::getline(f,line)){

        for(int i=0; i<line.size(); ++i){
            if(line[i]=='=' || line[i]==',' || line[i] == ';'){
                line[i] = ' ';
            }
        }

        std::istringstream ss(line);
        
        string s;
        string v;
        int f;

        ss >> s >> v >> s >> s >> s >> f >> s >> s >> s >> s;
        
        if(f > 0){
            fcnt++;
        }

        int vid = 0;
        if(s2i.count(v)){
            vid = s2i[v];
            value[vid] = f;
        } else {
            vid = index;
            s2i[v] = index++;
            Adj.push_back(vector<int>());
            value.push_back(f);
        }

        while(ss >> s){
            int qid = 0;
            if(s2i.count(s)){
                qid = s2i[s];
                Adj[vid].push_back(qid);
            } else {
                qid = index;
                Adj[vid].push_back(index);
                s2i[s] = index++;
                Adj.push_back(vector<int>());
                value.push_back(0);
            }
        }
    }

    int n = value.size();

    vector<vector<int>> Adx(n, vector<int>());
    vector<int> valx(n,0);
    
    int i1 = 0;
    int i2 = fcnt;
    map<int,int> i2i;
    for(int i=0; i<n; ++i){
        if (value[i] > 0){
            valx[i1] = value[i];
            i2i[i] = i1;
            i1++;
        } else {
            i2i[i] = i2;
            i2++;
        }
    }
    value = valx;

    for(int i=0; i<n; ++i){
        int it = i2i[i];
        for(int j=0; j<Adj[i].size(); ++j){
            Adx[it].push_back(i2i[Adj[i][j]]);
        }
    }

    Adj = Adx;


    vector<vector<vector<int>>> DP(31, vector<vector<int>>(n, vector<int>(1<<15, -1)));
    DP[0][fcnt][0] = 0;

    for(int i=0; i<30; ++i){
        for(int j=0; j<n; ++j){
            for (int s = 0; s < 1<<fcnt; ++s) {
                int curr = DP[i][j][s];
                if(curr == -1) continue;
                int sum = 0;
                if(value[j] > 0 && 0==(s & 1<<j)){
                    int val = curr + (30-i-1) * value[j];
                    int code = s | (1<<j);
                    if(DP[i+1][j][code] < val){
                        DP[i+1][j][code] = val;
                    }
                }
                for(int nxt : Adj[j]){
                    if(DP[i+1][nxt][s] < curr){
                        DP[i+1][nxt][s] = curr;
                    }
                }
            }
        }
    }

    int mx = -1;
    for(int j=0; j<n; ++j){
        for(int s =0; s < 1<<fcnt; ++s){
            if(mx < DP[30][j][s]){
                mx = DP[30][j][s];
            }
        }
    }

    score = mx;

    std::cout << score << std::endl;
    std::cout << score2 << std::endl;

    std::cout << std::endl << "Execution Complete"<< std::endl;
    return 0;
    }
