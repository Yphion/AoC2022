#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <limits.h>

using namespace std;

struct Monkey {
    int type;
    long val;
    string a;
    string b;

    Monkey *aa;
    Monkey *bb;

    bool clean = false;

    Monkey(int op, int v, string one, string two, bool c) : type(op), val(v), a(one), b(two), clean(c){}
};

long string_to( const std::string& s )
{
  std::istringstream ss( s );
  long result;
  ss >> result >> std::ws;
  if (ss.eof()) return result;
  return -1; 
}

long eval(map<string, int> &mmap, vector<Monkey> &M, Monkey *m){
    long res = 0;
    if(m->type=='v'){
        return m->val;
    } else if(m->type == '+'){
        res= eval(mmap, M, m->aa)+eval(mmap, M, m->bb);
    } else if (m->type == '-'){
        res= eval(mmap, M, m->aa)-eval(mmap, M, m->bb);
    } else if (m->type == '*'){
        res= eval(mmap, M, m->aa)*eval(mmap, M, m->bb);
    } else if (m->type == '/'){
        res= eval(mmap, M, m->aa)/eval(mmap, M, m->bb);
    } else if (m->type == '='){
        return (eval(mmap, M, m->aa) == eval(mmap, M, m->bb)) ? 1 : 0;
    } else {
        cout << "Op not found: " << m->type << endl;
    }

    if(m->aa->clean && m->bb->clean){
        m->type = 'v';
        m->val = res;
        m->clean = true;
    }

    return res;
}

int main(){
    
    std::string line;
    
    std::cout << "Running Program"<< std::endl << std::endl;


    long score = 0;
    long score2 = 0;

    map<string, int> mmap;
    
    int index = 0;

    vector<Monkey> M;

    while(std::getline(cin,line)){

        for(int i=0; i<line.size(); ++i){
            if(line[i]==':'){
                line[i] = ' ';
            }
        }
        std::istringstream ss(line);
        string a, b, c;
        char op;
        bool cl = false;
        ss >> a >> b;
        long val = string_to(b);
        if(val != -1){
            op = 'v';
            b = "";
            c = "";
            if (a!= "humn"){
                cl = true;
            } else {
                b = "y";
            }
        } else {
            ss >> op >> c;
        }
        Monkey m(op, val, b, c, cl);
        M.push_back(m);
        mmap[a] = index++;
    }

    for(int i=0; i<M.size(); ++i){
        Monkey &m = M[i];
        m.aa = &M[mmap[m.a]];
        m.bb = &M[mmap[m.b]];
    }

    score = eval(mmap, M, &M[mmap["root"]]);
    

    Monkey &root = M[mmap["root"]];
    root.type = '-';
    //int id = ;
    Monkey *m = &M[mmap["humn"]];
    
    long res = 0;
    
    Monkey &curr = root;
    
    while(curr.a != "y"){
      if(curr.aa->clean){
        if(curr.type=='+'){
          res -= curr.aa->val;
        } else if (curr.type == '*'){
          res /= curr.aa->val;
        } else if (curr.type == '/'){
          res = curr.aa->val / res;
        } else if (curr.type == '-'){
          res = curr.aa->val - res;
        } else {
          break;
        }
        curr = *curr.bb;
      } else if (curr.bb->clean) {
        if(curr.type=='+'){
          res -= curr.bb->val;
        } else if (curr.type == '*'){
          res /= curr.bb->val;
        } else if (curr.type == '/'){
          res *= curr.bb->val;
        } else if (curr.type == '-'){
          res += curr.bb->val;
        } else {
          break;
        }
        curr = *curr.aa;
      } else {
        break;
      }
  
    }
    
    score2 = res;

    std::cout << score << std::endl;
    std::cout << score2 << std::endl;

    std::cout << std::endl << "Execution Complete"<< std::endl;
    return 0;
    }
