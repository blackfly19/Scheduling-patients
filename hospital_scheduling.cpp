#include<bits/stdc++.h>
using namespace std;

#define population 50
#define generations 100
#define mutation_rate 0.29
#define crossover_rate 0.85

vector <int> random_num_gen(vector <int> v)
{
	unsigned seed = rand();
	shuffle(v.begin(),v.end(),default_random_engine(seed));
	return v;
}

class patient
{
public:
	int completionTime;
	int triage;
	int noOp;
	patient()
	{
		completionTime = 0;
	}
};
class genome
{
public:
	vector <int> chromosome;
	int fitness;
	genome(vector <int> chromosome)
	{
		this->chromosome = chromosome;
	}
	void Fitness(patient *details,int n)
	{
		int value = 0;
		for(int i=0;i<n;i++)
			value += (details[i].completionTime * details[i].triage);
		fitness = value;
	}
};
bool operator<(const genome &gen1,const genome &gen2)
{
	return gen1.fitness < gen2.fitness;
}
void single_point_crossover(vector <int> &v1,vector <int> v2)
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
}

void mutate(vector <int> &v)
{
	int len = v.size();
	int pos1 = rand()%len;
	int pos2 = rand()%len;

	swap(v[pos1],v[pos2]);
}
int main()
{
	srand(unsigned(time(0)));	

	int n,totNoOp=0;
	patient *details;
	vector <genome> all_gen;
	vector <int> gen;
	vector <int> completionTime;
	unordered_map<int,pair<int,int>> operationNo;


	cout<<"ENTER NUMBER OF PATIENTS: ";
	cin>>n;
	details = new patient[n];
	for(int i=0;i<n;i++)
	{
		cout<<"\nENTER TRIAGE FACTOR: ";
		cin>>details[i].triage;
		cout<<"\nENTER NUMBER OF OPERATIONS: ";
		cin>>details[i].noOp;
		for(int j=0;j<details[i].noOp;j++)
		{
			int num;
			cout<<"ENTER OPERATION "<<j+1<<"'s COMPLETION TIME: ";
			cin>>num;
			completionTime.push_back(num);
			totNoOp++;
			operationNo[totNoOp] = make_pair(i,j);
		}
	}
	for(int i=1;i<=totNoOp;i++)
		gen.push_back(i);
	for(int i=0;i<population;i++)
		all_gen.push_back(genome(random_num_gen(gen)));

	for(int i=0;i<population;i++)
	{
		int time = 0;
		for(auto j = all_gen[i].chromosome.begin();j != all_gen[i].chromosome.end();j++)
		{
			time += completionTime[*j-1];
			details[operationNo[*j].first].completionTime = time;
		}
		all_gen[i].Fitness(details,n);
	}
	sort(all_gen.begin(),all_gen.end());


	for(int k=0;k<generations;k++)
	{
		//calculating fitness values and completion time
		
		vector <genome> new_gen;
		vector <float> prob;
		float sum_of_prob = 0.0;

		//elitism 10% of population
		int s = (10*population)/100;
		for(int i=0;i<s;i++)
			new_gen.push_back(all_gen[i]);

		//single point crossover
		for(int i=0;i<population;i++)
		{
			int prob = ((rand()%99)+1)/100;

			if(prob < crossover_rate)
			{
				int parent_index;
				if(i != 0)
					parent_index = i - 1;
				else
					parent_index = i + 1;
				single_point_crossover(all_gen[i].chromosome,all_gen[parent_index].chromosome);
			}
		}

		//mutation
		for(int i=0;i<population;i++)
		{
			int prob = ((rand()%99)+1)/100;

			if(prob < mutation_rate)
			{
				mutate(all_gen[i].chromosome);
			}
			
		}

		//roulette wheel selection mechanism
		for(int i=0;i<population-s;i++)
		{
			float pr = float(1.0/all_gen[i].fitness);
			prob.push_back(pr);
			sum_of_prob += pr;
		}
		for(int i=0;i<population-s;i++)
		{
			prob[i] = prob[i]/sum_of_prob;
		}
		for(int i=0;i<population-s;i++)
		{
			float ran = (float)((rand()%99)+1)/100;
			int index = 0;
			float select = 0.0;
			while(select < ran && index < population)
				select = select + prob[index++];
			new_gen.push_back(all_gen[index]);
		}


		all_gen = new_gen;

		for(int i=0;i<population;i++)
		{
			int time = 0;
			for(auto j = all_gen[i].chromosome.begin();j != all_gen[i].chromosome.end();j++)
			{
				time += completionTime[*j-1];
				details[operationNo[*j].first].completionTime = time;
			}
			all_gen[i].Fitness(details,n);
		}
		sort(all_gen.begin(),all_gen.end());

		/*code for checking
		   for(auto j = all_gen[0].chromosome.begin();j != all_gen[0].chromosome.end();j++)
			cout<<*j<<" ";
		cout<<"Fitness: "<<all_gen[0].fitness<<"\n";*/
		
	}

	for(auto j = all_gen[0].chromosome.begin();j != all_gen[0].chromosome.end();j++)
			cout<<"Patient "<<operationNo[*j].first+1<<" ,Operation "<<operationNo[*j].second+1 <<"\n";
}
