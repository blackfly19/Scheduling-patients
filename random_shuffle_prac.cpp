#include<bits/stdc++.h>
using namespace std;
vector <int> random_num_gen(vector <int> v)
{
	//srand(unsigned(time(0)));
	//int arr[] = {1,2,3,4,5,6,7,8,9,10,11};
	unsigned seed = rand();

	shuffle(v.begin(),v.end(),default_random_engine(seed));
	return v;

}
int main()
{
	srand(unsigned(time(0)));
	vector <int> arr{1,2,3,4,5,6,7,8,9,10,11};
	arr = random_num_gen(arr);
	//unsigned seed = rand();
	//shuffle(arr,arr+11,default_random_engine(seed));
	this_thread::sleep_for(chrono::milliseconds(10000));
	for(int i=0;i<11;i++)
		cout<<arr[i]<<" ";
}
