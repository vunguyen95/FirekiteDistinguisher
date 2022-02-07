#include<iostream>
#include<iomanip>
#include<vector>
#include"headers/matrix.h"
using namespace std;
vector<vector<char>> mmul(vector<vector<char>>& u, vector<vector<char>>& v)
{	
	int m= u.size();
	int n= u[0].size();
	int p= v.size();
	int q = v[0].size();
	int i{0},j{0},k{0};
	vector<vector<char>> res(m);
	if(n!=p)
	{
		cout << "Wrong format"<<endl;
	}
	else
	{
		for(i=0; i< m; i++)
		{
			res[i].resize(q);
		}
		i = 0;
		while(i<m)
		{	
			for(j=0;j<q;j++)
			{
				for(k=0;k<n;k++)
				{
					res[i][j] += u[i][k]*v[k][j];
				}
			}
			i++;
		}
		

	}
	return res;
}
vector<char> mul(vector<char>& b, vector<vector<char>>& a)// in binary, of the form b.A
{
	int m = a.size();
	int n = a[0].size();
	int p = b.size();
	int i{ 0 }, j{ 0 }, k{ 0 };
	vector<char> res(n);
	if (m != p)
		cout << "Wrong format:" << endl;
	else
	{
		while (i < n)
		{
			for (j = 0; j < m; j++)
			{
				res[i] += (a[j][i] * b[j]);
				res[i] = res[i] % 2;
			}
			i++;
		}
	}
	return res;
}
char scalar(vector<char>& u, vector<char>& v)
{
	char res{ 0 };
	if (u.size() != v.size())
	{
		cout << " Wrong format:";
	}
	else 
	{
		for (int i = 0; i < u.size(); i++)
		{
			res += u[i] * v[i];
		}
	}
	return res % 2;
}

vector<vector<char>> keygen(int& n, int& m, int& b)
{
	vector<char> key(b);
	srand((unsigned)time(0));
	for (int i = 0; i < b; i++)
	{
		key[i] = rand() % 2;
	}
	vector<vector<char>> q;
	q.push_back(key);
	for (int i = 2; i <= m; i++)
	{
		vector<char> temp(b);
		temp[b-1] = q.back()[0];
		for (int j = 0; j < b-1; j++)
		{
			temp[j] = q.back()[j + 1];
		}
		q.push_back(temp);
	}
	for (int i = 0; i < m; i++)
	{
		q[i].resize(n);
	}
	return q;
}

vector<char> add( vector<char>& u,  vector<char>& v, int& length)// for the vectors, using as XOR.
{
	//int n = u.size();
	vector<char> res(length);
	if(u.size() != v.size())
	{
		cout << "Wrong format, check size again";
	}
	else
	{
		for (int i = 0; i < length; i++)
		{
			res[i] = (u[i] + v[i]) % 2;
		}
	}
	return res;
}
int weight(vector<char>& v, int& length)
{
	int res = 0;
	for (int i = 0; i < length; i++)
	{
		if (v[i] == 1)
		{
			res += 1;
		}
	}
	return res;
}


