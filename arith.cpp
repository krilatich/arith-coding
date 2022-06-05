#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
using namespace std;

	map<char, pair<double,double> > m; 
	map<char,double> sym_freq;
	





int main(int argc, char* argv[])
{
	
	ifstream f("input.txt", ios::out | ios::binary);
	ofstream g("encode.txt", ios::out | ios::binary);


	int count  = 0;
	string in;

char c;
c = f.get();

	while (!f.eof())
	{
	
		
		in+=c;
		m[c].first++;
		count++;
		c=f.get();
	
	}
	



double high = 1.0;
double low = 0.0;


for (map<char, pair<double,double> >::iterator itr = m.begin(); itr != m.end(); ++itr)
	{
		
		itr->second.first/=count;
		sym_freq[itr->first] = 	itr->second.first;
	
		
		
		itr->second.first = low;
		itr->second.second = itr->second.first + sym_freq[itr->first];
		low = itr->second.second;
	
	}
	
	
		
  
 
	return 0;
}