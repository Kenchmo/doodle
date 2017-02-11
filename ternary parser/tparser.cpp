//
//  main.cpp
//  Ternary Parser
//
//  Created by Lufan Zhou on 2/9/17.


/**
 * This program accepts a line of input from the user.
 * The input should be an expression in ternary logic with the operations AND, OR, and NOT. 
 * NOT should have a higher precedence than AND and OR. AND and OR have the same precedence and
 * should be evaluated left to right. The input can also contain parentheses to enforce
 * specific order of evaluation.
**/
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <string>

using namespace std;

string logic_processor(vector<string> v){
    for(string it:v) cout<<it<<endl;
    if(v.size() == 2){
        if(v[0] != "NOT") return "invalid";
        else{
            if(v[1] == "T") return "F";
            else if(v[1] == "F") return "T";
            else if(v[1] == "U") return "U";
            else return "invalid";
        }
    }
    string expr = v[0] + " " + v[1] + " " + v[2];
    expr = expr.substr(expr.find_first_not_of(" "), expr.length());
    cout<<"processing: "<<expr<<endl;
    
    if(expr == "T AND T") return "T";
    if(expr == "T AND F") return "F";
    if(expr == "T AND U") return "U";
    
    if(expr == "F AND T") return "F";
    if(expr == "F AND F") return "F";
    if(expr == "F AND U") return "F";
    
    if(expr == "U AND T") return "U";
    if(expr == "U AND F") return "F";
    if(expr == "U AND U") return "U";
    
    
    if(expr == "T OR T") return "T";
    if(expr == "T OR F") return "T";
    if(expr == "T OR U") return "T";
    
    if(expr == "F OR T") return "T";
    if(expr == "F OR F") return "F";
    if(expr == "F OR U") return "U";
    
    if(expr == "U OR T") return "T";
    if(expr == "U OR F") return "U";
    if(expr == "U OR U") return "U";
    else return "invalid";
    
}


int main(){
    
    string input;
    string expr;
    cout<<"Please Enter the input: "<<endl;
    getline(cin, input, '\n');

    int j = 0;
    while(input.length() != 1){
        cout<<"--------------------------------------------------\n";
        cout<<"input processing brackets round "<<++j<<endl;
        cout<<"input: "<<input<<endl;
        size_t right = input.find_first_of(")");
        size_t left = input.find_last_of("(");
        cout<<"left: "<<left<<", right: "<<right<<endl;
        if((left == string::npos && right != string::npos) ||
           (left != string::npos && right == string::npos)){
            cout<<"unbalanced bracket invalid input"<<endl;
            return 0;
        }
        else if(left != string::npos && right != string::npos){
            expr = input.substr(left + 1, right - left - 1);
            input.erase(left, right-left+1);
            
        //    cout<<"input after removing brackets: "<<input<<endl;
            cout<<"get expr: "<<expr<<endl;
            while(expr.find("NOT") != string::npos){
                size_t i = expr.find("NOT");
                if(expr[i+4] == 'T') expr[i+4] = 'F';
                else if(expr[i+4] == 'F') expr[i+4] = 'T';
                expr.erase(i,4);
            }
            cout<<"expr after removing NOT: "<<expr<<endl;
        }
        else{
            left = input.find_first_not_of(" ");
            input.erase(0, left);
            expr = input;
            input.erase(0);
        }
        vector<string> v;
        istringstream buf(expr);
        for(string word; buf >> word; )
            v.push_back(word);

        int i = 0;
        while(v.size() != 1){
            cout<<"-------------------\n";
            cout<<"inside round "<<i++<<endl;
            string result = logic_processor(v);
            cout<<"result: "<<result<<endl;
            
            if(result == "invalid"){
                cout<<"invalid input"<<endl;
                return 0;
            }
            v[0] = result;
            if(v.size() >= 3) v.erase(v.begin() + 1, v.begin() + 3);
            if(v.size() == 2) v.erase(v.begin()+1);
        }
        if(left != string::npos) input.insert(left, " "+v[0]);
        else input = v[0];
        while(input[0] == ' ') input.erase(input.begin());
        cout<<"input after this round: "<<input<<endl;
    }
    cout<<"Result: "<<input<<endl;
    return 0;
}
