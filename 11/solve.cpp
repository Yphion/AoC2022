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

typedef CGAL::Gmpz Z;

struct Monkey {
    int id;
    string op;
    int opval;
    int t;
    int m1;
    int m2;

    int count;

    vector<Z> items;

    Monkey(int i, string o, int v, int d, int mt, int mf, vector<Z> &it) : id(i), op(o), opval(v), t(d), m1(mt), m2(mf), items(it) {}
};



long string_to( const std::string& s )
{
  std::istringstream ss( s );
  long result;
  ss >> result >> std::ws;
  if (ss.eof()) return result;
  return -1; 
}

int main(){
    std::ifstream f("input.txt");
    std::string line;
    
    std::cout << "Running Program"<< std::endl << std::endl;

    long score = 0;

    long gigaprod = 1;

    vector<Monkey> X;
    
    while(std::getline(f,line)){
        if(line.size() == 0) continue;
        
        int id, opval, t, m1, m2;
        string op;

        sscanf(line.c_str(),"Monkey %i", &id);

        std::getline(f,line);
        std::replace(line.begin(), line.end(), ',', ' ');
        std::istringstream ss(line);
        string tmp;
        ss >> tmp >> tmp;
        vector<Z> items;
        int item;
        while(ss >> item){
            items.push_back(Z(item));
        }

        std::getline(f,line);
        std::istringstream sss(line);

        string optmp;

        sss >> tmp >> tmp >> tmp>> tmp >> op >> optmp;

        int v = (int)string_to(optmp);
        if(v == -1){
            op = "^";
            opval = 2;
        } else {
            opval = v;
        }

        std::getline(f,line);
        std::istringstream ss3(line);
        ss3 >> tmp >> tmp >> tmp >> t;

        gigaprod *= t;

        std::getline(f,line);
        sscanf(line.c_str(),"If true: throw to monkey %i", &m1);
        std::istringstream ss4(line);
        ss4 >> tmp >> tmp >> tmp >> tmp >> tmp >> m1;

        std::getline(f,line);
        sscanf(line.c_str(),"If false: throw to monkey %i", &m2);
        std::istringstream ss5(line);
        ss5 >> tmp >> tmp >> tmp >> tmp >> tmp >> m2;

        X.push_back(Monkey(id, op, opval, t, m1, m2, items));
    }

    vector<Z> Y(X.size(),0L); 

    //20 for task 1
    for(int i=0; i<10000; ++i){
        for(int j = 0; j<X.size(); ++j){
            Monkey &m = X[j];
            for (Z x : m.items){
                Y[j]++;

                if(m.op == "*"){
                    x = x*m.opval;
                } else if(m.op == "+"){
                    x = x+m.opval;
                } else {
                    x = x*x;
                }

                x %= gigaprod;

                //x /= 3; //for task 1

                if (x % m.t == 0){
                    X[m.m1].items.push_back(x);
                } else {
                    X[m.m2].items.push_back(x);
                }
            }
            m.items.clear();
        }
    
    }
    sort(Y.begin(), Y.end());

    std::cout << (Y[Y.size()-1]*Y[Y.size()-2]) << std::endl;

    std::cout << std::endl << "Execution Complete"<< std::endl;
    return 0;
    }
