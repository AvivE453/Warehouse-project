#include <iostream>
#include <fstream>
#include "../include/Parse.h"
using namespace std;

void Parse::ParseFile(string configorationFile)
{
    ifstream myFile(configorationFile);
    string myline;
    while (myFile)
    {
        getline(myFile, myline);
        vector<string> words = tokenize(myline, " ");
        for (string w : words)
        {
            cout << w << endl;
        }
        string first = words[0];
        cout << "first: " << first << endl;
        if (first == "customer")
            cout << "a costumer: ";
        else if (first.data() == "volunteer")
        {
            cout << "a volunteer: ";
        }
        else
            cout << "bad line: " << endl;
        //  cout << myline;
        myFile >> ws;
        if (!myFile)
            break;
    }
    myFile.close();
}
vector<string> Parse::tokenize(string s, string del)
{
    vector<string> words;
    int start, end = -1 * del.size();
    do
    {
        start = end + del.size();
        end = s.find(del, start);
        words.push_back(s.substr(start + 1, end - start));
    } while (end != -1);
    return words;
}
