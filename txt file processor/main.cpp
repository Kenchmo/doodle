#include <vector>
#include <iostream>
#include <fstream>
#include <string>


using namespace std;


int main(){

    ifstream in_stream;
    string line;
    string temp;
    size_t index;
    in_stream.open("input.txt");
    ofstream myfile;
    myfile.open ("example.txt");
    while(!in_stream.eof()){
        in_stream >> line;
        index = line.find_first_of("abcdefghijklmnopqrstuvwxyz");
        if(index != string::npos){
        	line = line.substr(index);
        	myfile << line<<endl;
        }
        
    }
    in_stream.close();
  	
  	myfile.close();
  	return 0;
}