#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <optional>


using namespace std;

long string_to( const std::string& s )
{
  std::istringstream ss( s );
  long result;
  ss >> result >> std::ws;
  if (ss.eof()) return result;
  return -1; 
}

long rec(vector<map<string,int>> &adj, vector<long> &val, int node){
    map<string,int>::iterator it;
    for(auto const &x : adj[node]){
        val[node] += rec(adj, val, x.second);
    }
    return val[node];
}

int main(){
    std::ifstream f("input.txt");
    std::string line;
    
    std::cout << "Running Program"<< std::endl << std::endl;


    long score = 0;
    long score2 = 0;
    
    int n = 1;

    vector<int> visited (1,0);
    vector<long> val(1,0);

    vector<map<string,int>> adj(1, map<string,int>());

    vector<int> stack(1, 0);

    while(std::getline(f,line)){

        int curr = stack.back();

        std::istringstream ss(line);
        long a; string s1, s2, s3; 
        ss >> s1;

        a = string_to( s1 );
        if(a != -1){
            if(visited[curr] == 1){
                val[curr] += a;
            }
        } else {
            ss >> s2;
            if(s1 == "$"){
                if(visited[curr] == 1){
                    visited[curr] = 2;
                }

                

                if(s2 == "cd"){
                    //cd

                    ss >> s3;
                    if(s3 == ".."){
                        stack.pop_back();
                    } else {
                        if (adj[curr].count(s3)){
                            
                        } else {
                            visited.push_back(0);
                            val.push_back(0);
                            adj[curr][s3] = n;
                            adj.push_back(map<string,int>());
                            n++;
                        }
                        stack.push_back(adj[curr][s3]);
                        
                    }
                } else {
                    //ls
                    
                    if(visited[curr] == 0){
                        visited[curr] = 1;
                    } 
                    
                }
            } else {
                //dir
                if (adj[curr].count(s3)){
                    //
                } else {
                    visited.push_back(0);
                    val.push_back(0);
                    adj[curr][s2] = n;
                    adj.push_back(map<string,int>());
                    n++;
                }
            }
        }
        
    }

    rec(adj, val, 0);

    long available = (70000000-val[0]);
    long more = 30000000-available;

    for(int i=1; i<val.size(); ++i){
        if (val[i] <= 100000){
            score += val[i];
        }
    }

    score2 = val[0];

    for(int i=1; i<val.size(); ++i){
        if (val[i] >= more && val[i] < score2){
            score2 = val[i];
        }
    }


    std::cout << score << std::endl;
    std::cout << score2 << std::endl;

    std::cout << std::endl << "Execution Complete"<< std::endl;
    return 0;
    }
