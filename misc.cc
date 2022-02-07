#include<iostream>
#include"headers/misc.h"
#include<vector>
#include<set>
#include<unordered_map>
using namespace std;
std::ostream& operator<<(ostream& os, const vector<char>& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		os << static_cast<int>(v[i]) << " ";
	}
	os << endl;
	return os;
}
std::ostream& operator<<(ostream& os, const vector<vector<char>>& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		for (int j = 0; j < v[i].size(); j++)
		{
			os << static_cast<int>(v[i][j]) << " ";
		}
		os << endl;
	}
	return os;
}
std::ostream& operator<<(ostream& os, const set<vector<char>>& s)
{
	for (auto it = s.begin(); it != s.end(); it++)
	{
		auto vec = *it;
		os << vec;
	}
	return os;
}
