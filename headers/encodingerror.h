#ifndef ENCODINGERROR_H
#define ENCODINGERROR_H
#include<math.h>
#include<vector>
#include<algorithm>
using namespace std;

// Here we decode c_e of length klogn into the next-iteration error vector of PRNG. Each block of length logn encoding the error position in binary form.
int bti(vector<char>& v);
vector<char> itb(int& n, int& length);
vector<char> errordecoder(vector<char>& ce, int& k, int& n);

#endif // !ENCODINGERROR_H
