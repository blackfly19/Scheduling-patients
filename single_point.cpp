#include<bits/stdc++.h>
using namespace std;

void display(vector <int> v)
{
	for(auto i = v.begin();i != v.end();i++)
		cout<<*i<<" ";
	cout<<"\n";
}

void single_point_crossover(vector <int> &v1,vector <int> &v2)
{
	int len = v1.size();
	vector <int> pos[len];
	vector <int> zeros;
	unsigned seed = rand()%len;
	for(int i = seed;i < len;i++)
		swap(v1[i],v2[i]);	

	for(int i=0;i<len;i++)
		pos[v1[i]-1].push_back(i);	

	for(int i=0;i<len;i++)
	{
		if(pos[i].size() > 1)
		{
			int prob = rand()%2;
			if(prob == 0)
			{
				v1[pos[i].at(1)] = 0;
				zeros.push_back(pos[i].at(1));
			}
			else
			{
				v1[pos[i].at(0)] = 0;
				zeros.push_back(pos[i].at(0));
			}
		}
	}
	int zero_len = zeros.size();
	for(int i=0;i<len;i++)
	{
		if(pos[i].size() == 0)
		{
			int val = rand()%zero_len;
			v1[zeros[val]] = i+1;
			zeros.erase(zeros.begin()+val);
			zero_len--;
		}
	}
	for(int i=0;i<len;i++)
		pos[i].clear();
	for(int i=0;i<len;i++)
		pos[v2[i]-1].push_back(i);	
	zeros.clear();
	for(int i=0;i<len;i++)
	{
		if(pos[i].size() > 1)
		{
			int prob = rand()%2;
			if(prob == 0)
			{
				v2[pos[i].at(1)] = 0;
				zeros.push_back(pos[i].at(1));
			}
			else
			{
				v2[pos[i].at(0)] = 0;
				zeros.push_back(pos[i].at(0));
			}
		}
	}
	zero_len = zeros.size();
	for(int i=0;i<len;i++)
	{
		if(pos[i].size() == 0)
		{
			int val = rand()%zero_len;
			v2[zeros[val]] = i+1;
			zeros.erase(zeros.begin()+val);
			zero_len--;
		}
	}
}


int main()
{
	srand(unsigned(time(0)));
	vector <int> v1{2,3,1,4,5};
	vector <int> v2{4,2,3,5,1};

	single_point_crossover(v1,v2);
	display(v1);
}
