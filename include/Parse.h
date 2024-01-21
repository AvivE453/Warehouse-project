#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;



class Parse {
    public:
        void ParseFile(string configorationFile);
        vector<string> tokenize(string s, string del);
};