#ifndef MISC_H
#define MISC_H
#include<iostream>
#include<vector>
#include<set>
#include<unordered_map>
using namespace std;
std::ostream& operator<<(ostream& os, const vector<char>& v);
std::ostream& operator<<(ostream& os, const vector<vector<char>>& v);
std::ostream& operator<<(ostream& os, const set<vector<char>>& s);

#endif // !MISC_H
