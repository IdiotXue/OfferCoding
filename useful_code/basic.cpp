// Includes
#include <string.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iterator>
using namespace std;

// Macros
typedef long double ld;
typedef long long ll;
template <class T>
T MIN(const T &x, const T &y) { return x < y ? x : y; }
template <class T>
T MAX(const T &x, const T &y) { return x > y ? x : y; }
template <class T>
T ABS(const T &x) { return x > 0 ? x : -x; }
template <class T>
void SWAP(T &x, T &y)
{
	T z = x;
	x = y;
	y = z;
}
const ld PI = 3.14159265358979323846;
const ld EPSILON = 1;

// General parsing/formatting
ll toInt(string s)
{
	stringstream in(s, ios_base::in);
	ll result;
	in >> result;
	return result;
}
ld toDouble(string s)
{
	stringstream in(s, ios_base::in);
	ld result;
	in >> result;
	return result;
}
string toString(ll n)
{
	stringstream out(ios_base::out);
	out << n;
	return out.str();
}
string toString(ld d, int precision = -1)
{
	stringstream out(ios_base::out);
	if (precision >= 0)
	{
		out.precision(precision);
		out.setf(ios::fixed);
	}
	out << d;
	string s = out.str();
	bool nonZero = false;
	for (int i = 0; i < s.size(); i++)
		if (s[i] != '0' && s[i] != '-' && s[i] != '.')
			nonZero = true;
	if (s[0] == '-' && !nonZero)
		return s.substr(1);
	else
		return s;
}
string toString(int n) { return toString((ll)(n)); }
string toString(char ch)
{
	string s = "?";
	s[0] = ch;
	return s;
}
string toString(const string &s) { return s; }
template <class U, class V>
string toString(pair<U, V> u) { return toString("(") + toString(u.first) + "," + toString(u.second) + ")"; }
template <class T>
string toString(const vector<T> &v, string delim = ",")
{
	string s = "(";
	for (int i = 0; i < v.size(); i++)
	{
		if (i != 0)
			s += delim;
		s += toString(v[i]);
	}
	return s + ")";
}
template <class T>
string toString(const set<T> &t, string delim = ",")
{
	string s = "{";
	for (typename set<T>::const_iterator it = t.begin(); it != t.end(); it++)
	{
		if (it != t.begin())
			s += delim + " ";
		s += toString(*it);
	}
	return s + "}";
}
template <class U, class V>
string toString(const map<U, V> &m, string delim = ",")
{
	string s = "{";
	for (typename map<U, V>::const_iterator it = m.begin(); it != m.end(); it++)
	{
		if (it != m.begin())
			s += delim + " ";
		s += toString(it->first) + "->" + toString(it->second);
	}
	return s + "}";
}

int getNumWords(string s, string delim = " ")
{
	int count = 0;
	for (int i = 0; i < s.size(); i++)
		if ((i == 0 || delim.find(s[i - 1]) != -1) && delim.find(s[i]) == -1)
			count++;
	return count;
}
string getWord(string s, int j, string delim = " ")
{
	int count = 0;
	string t;
	for (int i = 0; i < s.size(); i++)
	{
		if (delim.find(s[i]) == -1)
			t += s[i];
		else
		{
			if (i != 0 && delim.find(s[i - 1]) == -1)
				count++;
			if (count > j)
				return t;
			t = "";
		}
	}
	return t;
}
string getDelimiter(string s, int j, string delim = " ")
{
	int count = 0;
	string t;
	for (int i = 0; i < s.size(); i++)
	{
		if (delim.find(s[i]) != -1)
			t += s[i];
		else
		{
			if (i == 0 || delim.find(s[i - 1]) != -1)
				count++;
			if (count > j)
				return t;
			t = "";
		}
	}
	return t;
}

// Basic math
bool isEqual(ld v1, ld v2) { return ABS(v1 - v2) < EPSILON; }
bool isLess(ld v1, ld v2) { return v1 - v2 < -EPSILON; }
ll gcd(ll n1, ll n2) { return n2 == 0 ? ABS(n1) : gcd(n2, n1 % n2); }
ll lcm(ll n1, ll n2) { return n1 == 0 && n2 == 0 ? 0 : ABS(n1 * n2) / gcd(n1, n2); }

// for line input.
/*
		while(getline(cin, str) ){
			vector<string> ss = split(str, ' ');
			vector<int> tmp;
			for (int i = 0; i < ss.size(); ++i) {
				tmp.push_back(toInt(ss[i]));
			}
			M.push_back(tmp);
		} 
*/
template <typename Out>
void split(const std::string &s, char delim, Out result)
{
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		*(result++) = item;
	}
}
std::vector<std::string> split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}

// for multiple lines input.
// int t;
// cin >> t;
// while (t--) {

// debug method.
/* FILE *file;
freopen("test.txt", "r", stdin);
*/

using namespace std;

/* DESCRIPTION: 

*/

/* MAIN POINTS:
	1. 
	2.
	...

*/

class Solution
{
  public:
	// solution.
};

int main(int argc, char *argv[])
{
	// input process.

	// main process.
}