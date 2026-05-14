#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
using namespace std;

namespace Utils
{
    string trim(const string &str);
    string to_lowercase(const string &str);
    vector<string> split(const string &s, char delimiter);
}

#endif
