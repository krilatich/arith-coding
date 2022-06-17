#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
using namespace std;

	map<char, pair<double,double> > m; 
	map<char,double> sym_freq;
	
void narrowDown(double low, double high)
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
	
	ifstream f("encode.txt", ios::out | ios::binary);
	ofstream g("decode.txt", ios::out | ios::binary);

char c; double d;
c = f.get();

	while (c!='|')
	{
		f>>d;
		sym_freq[c] = d;
		
		f.get();
		c = f.get();
	}
	
	


double low = 0.0, high;

 
for (map<char, double >::iterator itr = sym_freq.begin(); itr != sym_freq.end(); ++itr)
	{
		
		m[itr->first].first = low;
		
		m[itr->first].second = m[itr->first].first + itr->second;
	
		low = m[itr->first].second;
	
	}



	



int n;
f>>n;

vector <bool> v;
int count = 0;
f.get();
char byte = f.get();

while (!f.eof())
	{
		
			if(byte=='|')		{  //остался хвост
			
			int k;
			k = f.get()-48;
			byte = f.get();
		
		
	for(int i = 0; i<k ; i++){
		
			bool b = byte & (1 << (7 - i));
			v.push_back(b);
			
		}
		
		break;
		}
		
		
		
		
		bool b = byte & (1 << (7 - count));
		v.push_back(b);
		
			count++;
			if (count == 8) { count = 0; byte = f.get();  }
	
	}


double message = 0.0;
double temp = 2;

for(int i=0;i<v.size();i++){
	
	
	for(int j=0;j<i;j++)
 	temp*=2;
 	
 	if(v[i]) message+=(1/temp);
	
	temp=2;
}

cout<<message;
	high = 1.0;
	low = 0.0;
  
  while(n) {
  
  
  for (map<char, pair<double,double> >::iterator itr = m.begin(); itr != m.end(); ++itr)
	{
  	pair<double,double> p = itr->second;
	
		if(message>=p.first && message<=p.second) {
			  
					g<<itr->first;
  					narrowDown(p.first,p.second);
  					break;
  		
		  }
 
	}
	
	
	n--;
	
}
  
 
	return 0;
}