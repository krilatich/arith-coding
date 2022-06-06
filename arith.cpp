#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
using namespace std;

	map<char, pair<double,double> > m; 
	map<char,double> sym_freq;
	
void makeNarrow(double low, double high)
{
	double range = high - low;
	
  			for (map<char, pair<double,double> >::iterator itr = m.begin(); itr != m.end(); ++itr)
	{
		
		itr->second.first = low;
		itr->second.second = sym_freq[itr->first] * range+low;
		low = itr->second.second;
 	
	 }
}





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
	
	
			//encoding
			
	
	low = 0.0;

for (int i=0;i<in.length();i++)
	{
	
	double range = high - low;
  high = low + range * m[in[i]].second;
  low = low + range * m[in[i]].first; 
			//cout<<low<<" "<<high<<endl;

}
 g << low + (high-low)/2;


f.close();
g.close();



  //decoding
ifstream F("encode.txt", ios::out | ios::binary);
ofstream G("decode.txt", ios::out | ios::binary);
double message;
F>>message;

	high = 1.0;
	low = 0.0;
  
  while(count) {
  
  
  for (map<char, pair<double,double> >::iterator itr = m.begin(); itr != m.end(); ++itr)
	{
  	pair<double,double> p = itr->second;
	
		if(message>p.first && message<p.second) {
			  
					G<<itr->first;
  					makeNarrow(p.first,p.second);
  					break;
  		
		  }
 
	}
	
	
	count--;
	
}
  
 
	return 0;
}