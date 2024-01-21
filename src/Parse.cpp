#include <iostream>
#include <fstream>
#include "../include/Parse.h"
using namespace std;


void Parse::ParseFile(string configorationFile){   
    ifstream MyFile(configorationFile);
    string myline;
    while (getline (MyFile, myline)){
        vector<string> words = tokenize(myline, " ");
        for (string w : words) {
            cout << w << endl;
        }
        cout << "---------------------------------";
    {
        /* code */
    }
    

  }
  MyFile.close();
}
vector<string> Parse::tokenize(string s, string del)
{ 
    vector<string> words;
    int start, end = -1*del.size();
    do {
        start = end + del.size();
        end = s.find(del, start);
        words.push_back(s.substr(start, end - start));
    } while (end != -1);
    return words;
}
