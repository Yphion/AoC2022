#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>


using namespace std;

struct Weird {

    int opt = 0;
    int A;
    vector<Weird> B;

    Weird(int i) : opt(i) {}
    Weird(int i, int a) : opt(i), A(a) {} 
    Weird() : A(0) {}

};

// returns 0 if one == other , 1 if one < other and 2 if one > other
int good(Weird &one, Weird &other){

    cout << one.B.size() << " " << other.B.size() << endl;

    if(one.opt == 0 && other.opt == 0){
        if(one.A < other.A){
            return 1;
        } else if (one.A == other.A){
            return 0;
        } else {
            return 2;
        }
    }

    if(one.opt == 1 && other.opt == 1){

        if(one.B.size() == 0){
            if(other.B.size() == 0){
                return 0;
            } else {
                return 1;
            }
        } else if(other.B.size() == 0){
            return 2;
        }

        int i = 0;
        while(i < one.B.size() && i < other.B.size()){
            int tmp = good(one.B[i], other.B[i]);
            if(tmp > 0) return tmp;
            i++;
        }
        if(i < one.B.size()){
            return 2;
        } else if(i < other.B.size()) {
            return 1;
        } else {
            return 0;
        }
    }

    if(one.opt == 0 && other.opt == 1){
        one.opt = 1;
        one.B.push_back(Weird(0, one.A));
        return good(one, other);
    } else if (one.opt == 1 && other.opt == 0){
        other.opt = 1;
        other.B.push_back(Weird(0, other.A));
        return good(one, other);
    } else {
        cout << "Unreachable code" << endl;
    }

}

int main(){
    std::ifstream f("input.txt");
    std::string line;
    
    std::cout << "Running Program"<< std::endl << std::endl;

    long score = 0;
    long score2 = 0;
    
    Weird prev;

    // Packets for part two

    Weird divone(1);
    divone.B.push_back(Weird(1));
    divone.B[0].B.push_back(Weird(0,2));

    Weird divtwo(1);
    divtwo.B.push_back(Weird(1));
    divtwo.B[0].B.push_back(Weird(0,6));

    int div1 = 0;
    int div2 = 0;
    
    // Main loop

    int index = 1;
    while(std::getline(f,line)){
        
        // Parse file

        if (line.size() == 0) continue;

        Weird root(1);
        vector<Weird *> stack;
        stack.push_back(&root);
        int num = -1;

        for(int i=0; i<line.size(); ++i){
            Weird *curr = stack.back();
            char c = line[i];

            if(c == '['){
                (*curr).B.push_back(Weird(1));
                stack.push_back(&(*curr).B.back());
            } else if (c == ']') {
                if(num != -1) (*curr).B.push_back(Weird(0,num));
                num = -1;
                stack.pop_back();
            } else if (c==','){
                if (num != -1) (*curr).B.push_back(Weird(0,num));
                num = -1;
            } else {
                if(num == -1) num = 0;
                int val = c-'0';
                num = 10*num + val;
            }
        }

        // Check positions for task two

        int d1 = good(root, divone);
        if(d1 == 1){
            div1++;
        }
        int d2 = good(root, divtwo);
        if(d2 == 1){
            div2++;
        }

        // Compare packets for part one

        if(index %2 == 0){
            int res = good(prev, root);
            cout << res << endl;
            if(res == 1){
                score += index/2;
            }
        }

        prev = root;

        index++;
    }

    std::cout << score << std::endl;
    std::cout << (div1+1)*(div2+2) << std::endl;

    std::cout << std::endl << "Execution Complete"<< std::endl;
    return 0;
    }
