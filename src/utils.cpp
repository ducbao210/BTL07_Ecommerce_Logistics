#include "../include/utils.h"
#include <algorithm>
#include <sstream>
using namespace std;

namespace Utils
{
    string trim(const string &str)
    {
        size_t first = str.find_first_not_of(" \t\r\n");
        if (string::npos == first)
            return str;
        size_t last = str.find_last_not_of(" \t\r\n");
        return str.substr(first, (last - first + 1));
    }

    string to_lowercase(const string &str)
    {
        string res = str;
        transform(res.begin(), res.end(), res.begin(), ::tolower);
        return res;
    }

    vector<string> split(const string &s, char delimiter)
    {
        vector<string> tokens;
        string token;
        istringstream tokenStream(s);
        while (getline(tokenStream, token, delimiter))
        {
            tokens.push_back(token);
        }
        return tokens;
    }
}
