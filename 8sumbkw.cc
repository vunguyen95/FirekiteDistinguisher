#include<iostream>
#include<vector>
#include"headers/encodingerror.h"
#include"headers/matrix.h"
#include"headers/misc.h"
#include<fstream>
#include<unordered_map>
#include<boost/functional/hash.hpp>
#include<algorithm>
#include<ctime>
#include<cstdlib>
using namespace std;

template < typename SEQUENCE > struct seq_hash //Hash function for vectors
{
	long long int operator() (const SEQUENCE& seq) const
	{
		std::size_t hash = 0;
		//boost::hash_range(hash, seq.begin(), seq.end());
		for (auto &i : seq) { hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2); }
			return hash;
	}
};
using un_map = std::unordered_map< vector<char>, vector<vector<char>>, seq_hash<vector<char>> >; //note that the first element in the vector<vector<int>> shall be the tag to trace back.
using vecset = std::set<vector<char>>;


vector<char> firekite(vector<vector<char>>& q, vector<char>& omega, int& n, int& m, int&d, int& k) //Firekite generator
{
	vector<char> output(d);

	vector<char> v(omega.begin(), omega.begin() + m);
	vector<char> ce(omega.begin() + m, omega.begin() + m + k * log2(n));
	auto res = mul(v, q);
	auto e = errordecoder(ce, k, n);
	res = add(res, e, n);
	copy(res.begin(), res.begin() + d, output.begin());// extracting output
	copy(res.begin() + d, res.end(), omega.begin());//extracting omega
	return output;
}




inline void mapsort(un_map& m, vector<char>& v, int& key_length) //To store vectors in an un_ordered map, the key being bits we want to cancel when matching.
// The first element of the container is the tag (test version)
{
	vector<char> key(v.begin(), v.begin() + key_length);
	auto find = m.find(key);
	if (find == m.end())
	{
		vector<vector<char>> container;
		container.push_back(v);
		m.insert(make_pair(key, container));
	}
	else
	{
		(*find).second.push_back(v);
	}

}

inline void matching(un_map& m1, int& nextkeylength, int& d, un_map& target, int& samples)
{
	int check_num{0};
	for (auto map_it1 = m1.begin(); map_it1 != m1.end(); map_it1++)
	{	
		if(check_num <= 2*samples){
		for (int i = 0; i < (*map_it1).second.size()-1; i++)
		{
			for (int j = i+1; j < (*map_it1).second.size(); j++)
			{
				auto sum = add((*map_it1).second[i], (*map_it1).second[j], d);
				mapsort(target, sum, nextkeylength);
				check_num++;
			}
		}
		}
		else{break;}
	}
}
//ofstream out;
//ofstream out1;
int main()
{
	//PARAMETERS 
	int k = 4; // error weight
	int n = 256; // 128
	int m = 52; // 20
	int b = 269; // b bit key, b> n such that (x^b-1)/(x-1) is irreducible //139
	int r = 15; // number of randomization rounds.
	int samples = 3*pow(2, 14); 
	int d = n - m - k * log2(n);
	int block = log2(n);
	int cancel = 14;
	int filterWeight = 8*k*d/n+1;
	int key_length{ 0 };
	int nextkey_length{ 0 };
	int count{0};
	vector<char> zero(d);
	vector<char> g(d);
	vector<char> omega(m + k * log2(n));

	//nonce N
	srand((unsigned)time(0));
	for(int i = 0; i< m ; i++)
	{
		omega[i] = rand() % 2;
	}
	
	//Nonce C0
	cout << "Nonce C0:" << endl;
	for(int j = d; j < d+k; j++)
	{
	vector<char> c = itb(j,block);
	copy(c.begin(),c.end(),omega.begin()+m + (j-d)*log2(n));
	cout << c;
	}
	cout << "Nonce omega:" << endl;
	cout << omega;
	//generating matrix key
	auto q = keygen(n, m, b);
	cout << "SECRET KEY" << endl;
	cout << q.size() << endl << q.back().size() << endl;

	//Randomization for r rounds, guarantee the error to be somewhat random
	for (int i = 1; i <= r; i++)
	{
		g = firekite(q, omega, n, m, d, k);
	}

	//out.open("second.txt");
	//out1.open("final.txt");

	un_map list;
	un_map listFirst;
	un_map listSecond;


	//Firekite generator starts here
	key_length = cancel;
	
	for (int i = 1; i <= samples; i++)
	{
		g = firekite(q, omega, n, m, d, k);
		mapsort(list, g, key_length);
	}

	count = 0;
	for(auto check_num = list.begin(); check_num!= list.end();check_num++)
	{
		count+= (*check_num).second.size();
	}
	cout << count << endl;
	
	nextkey_length = 2 * cancel;//eliminate c bits
	matching(list, nextkey_length, d, listFirst, samples);
	
	count = 0;
	for(auto check_num = listFirst.begin(); check_num!= listFirst.end();check_num++)
	{
		count+= (*check_num).second.size();
	}
	cout << "Check size: "<<count << endl;
	

	nextkey_length = 3 * cancel;
	matching(listFirst, nextkey_length, d, listSecond, samples);//eliminate 2c bits
	
	count = 0;
	for(auto check_num = listSecond.begin(); check_num!= listSecond.end();check_num++)
	{
		count+= (*check_num).second.size();
	}
	cout << "Check size: "<<count << endl;

	for(auto map_it = listSecond.begin(); map_it!= listSecond.end(); map_it++)
	{
		//out << (*map_it).second;
		for(int i =0; i< (*map_it).second.size()-1;i++)
		{
			for( int j = i+1 ; j< (*map_it).second.size();j++)
			{
				auto sum = add((*map_it).second[i], (*map_it).second[j], d);
				if(weight(sum,d) <= filterWeight && sum!= zero)
				{
					//out1 << sum;
					cout << "Low weight sum:" << endl << sum;
				}
			}
		}
	}
	
}
