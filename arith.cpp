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

char c;
c = f.get();
int count = 0;

	while (!f.eof())
	{
	
		m[c].first++;
		c=f.get();
		count ++;
	
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
	
	
	for (map<char, double >::iterator itr = sym_freq.begin(); itr != sym_freq.end(); ++itr)
			g<<itr->first<<" "<<itr->second<<" ";
	
		g<<"|"<<count<<" ";
	 

			//encoding
			
	
	low = 0.0;
	f.clear(); f.seekg(0);


c = f.get();
while (!f.eof())
	{
		
	double range = high - low;
  high = low + range * m[c].second;
  low = low + range * m[c].first; 
			//cout<<low<<" "<<high<<endl;
			
		
			c = f.get();

}
 //g<<low+(high-low)/2<< " ";
 

 
f.close();



 double d = 0;
 int deg = 1;
 double temp=1;
 
 vector <bool> v;
 
 cout<<low<<" "<<high<<endl;
 
 while(d<low || d>high){
 	
 
 	for(int i=0;i<deg;i++)
 	temp*=2;
 	
 	d+=(1/temp);
 	
 	
 	
 	if(d>high) {
	 d-=(1/temp);
	 v.push_back(0);
	 
	 } else v.push_back(1);
 	
 	
 	deg++;
 		temp=1;
 
 }
 
 
 for(int i=0;i<v.size();i++)
cout<<v[i];
char buf;
count = 0;

	for (int n = 0; n < v.size(); n++)
		{
			buf = buf | v[n] << (7 - count);
			count++;
			if (count == 8) { count = 0;   g << buf; buf = 0; }
		}
		if(buf) g<<"|"<<count<<buf;

g.close();

 
 
	return 0;
}