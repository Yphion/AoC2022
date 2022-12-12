#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

using namespace std;

int main(){
    std::ifstream f("input.txt");
    std::string line;
    
    std::cout << "Running Program"<< std::endl << std::endl;


    long score = 0;
    long score2 = 0;
    
    std::vector<std::vector<int>> X;
    
    int start = 0;
    int end = 0;
    int index = 0;
    while(std::getline(f,line)){
        
        int n = line.size();
        X.push_back(std::vector<int>(n,0));
        for(int i=0; i<n; ++i){
            if(line[i] >= 'a'){
                X.back()[i] = line[i]-'a';
            } else {
                if(line[i] == 'S'){
                    start = index;
                    X.back()[i] = 0;
                } else {
                    end = index;
                    X.back()[i] = 'z'-'a';
                }
            }
            index++;
        }   
    }
    int n = X.size()*X[0].size();
    weighted_graph G(n);
    weight_map weights = boost::get(boost::edge_weight, G);

    for(int i=0; i<X.size(); ++i){
        for(int j=0; j<X[0].size(); ++j){
            if(i > 0 && X[i-1][j]-X[i][j] >= -1){
                weights[boost::add_edge(i*X[0].size()+j, (i-1)*X[0].size()+j, G).first] = 1;
            }

            if(i > 0 && X[i-1][j]-X[i][j] <= 1){
                weights[boost::add_edge((i-1)*X[0].size()+j, i*X[0].size()+j, G).first] = 1;
            }

            if(j > 0 && X[i][j-1]-X[i][j] >= -1){
                weights[boost::add_edge(i*X[0].size()+j, i*X[0].size()+j-1, G).first] = 1;
            }

            if(j > 0 && X[i][j-1]-X[i][j] <= 1){
                weights[boost::add_edge(i*X[0].size()+j-1, i*X[0].size()+j, G).first] = 1;
            }
        }
    }

    std::vector<int> dist_map(n);

    boost::dijkstra_shortest_paths(G, end,
        boost::distance_map(boost::make_iterator_property_map(
        dist_map.begin(), boost::get(boost::vertex_index, G))));
    
    index = 0;
    score2 = n;
    for(int i=0; i<X.size(); ++i){
        for(int j=0; j<X[0].size(); ++j){
            if(X[i][j] == 0 && dist_map[index] < score2){
                score2 = dist_map[index];
            }
            index++;
        }
    }

    score = dist_map[start];

    std::cout << score << std::endl;
    std::cout << score2 << std::endl;

    std::cout << std::endl << "Execution Complete"<< std::endl;
    return 0;
    }
