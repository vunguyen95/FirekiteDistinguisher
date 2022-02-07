#include<math.h>
#include<algorithm>
#include"headers/encodingerror.h"
#include<vector>
using namespace std;
int bti(vector<char>& v)
{
	int res = 0;
	for (int i = 0; i < v.size(); i++)
	{
		res = res + pow(2, v.size() - i - 1)*v[i];
	}
	return res;
}
vector<char> itb(int& n, int& length)
{	
	int a = n;
	vector<char> res(length);
	for (int i = 0; a > 0; i++)
	{
		res[length-1-i] = a % 2;
		a = a / 2;
	}
	return res;
}
vector<char> errordecoder(vector<char>& ce, int& k, int& n)
{
	vector<int> res1;
	vector<char> res2(n);
	int block = log2(n);
	auto it = ce.begin();
	for (int i = 1; i <= k; i++)
	{
		vector<char> temp(it + block * (i - 1), it + block * i);
		res1.push_back(bti(temp));
	}
	sort(res1.begin(), res1.end());
	for (int i = 0; i < res1.size(); i++) //note that res[i] can be 0 given 2^logn iterations
	{
		if (res1[i] != 0)
		{
			res2[res1[i]] = 1;
		}
		
	}
	return res2;
}
