#include<bits/stdc++.h>
using namespace std;
int main()
{
	vector <float> fitness;
	vector <float> prob;
	vector <float> next_gen;
	float sum = 0;

	for(int i=0;i<5;i++)
	{
		int num;
		cin>>num;
		sum = sum + num;
		fitness.push_back(num);
	}
	sort(fitness.begin(),fitness.end());
	for(int i=0;i<5;i++)
	{
		float val = (fitness[i]/sum);
		prob.push_back(val);
		cout<<val<<" ";
	}
	reverse(prob.begin(),prob.end());
	cout<<endl;
	for(int i=0;i<5;i++)
	{
		float ran = (float)((rand()%99)+1)/100;
		cout<<ran<<" ";
		int index = 0;
		float live = 0;
		while(live < ran && index < 5)
			live = live + prob[index++];
		next_gen.push_back(prob[index]);	
	}
	cout<<endl;
	for(auto i = next_gen.begin(); i != next_gen.end();i++)
		cout<<*i<<" ";	
}
