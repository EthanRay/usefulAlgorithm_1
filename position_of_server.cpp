//确定服务器的数量和位置
#include"huawei_ruantiao.h"
#include <time.h>
#include<math.h>
long seconds_first;

//控制退出
long EXIT_TIME=89;

//并行数
int parallel_number;

//变量长度与个数
int variable_length;
int variable_count;

//加噪声概率
int PAR_min,PAR_max,PAR;
//增加或者删除HMCR个服务器
int HMCR_max,HMCR_min,HMCR;

void global_search_or_local_search(const vector<int> &costs,int iteration_count,int com_node)
{
	if(iteration_count>=2)
	{
		bool global_search=false;
		bool local_search=false;
		if(costs[iteration_count]==costs[iteration_count-1]&&costs[iteration_count-1]==costs[iteration_count-2])
		{
			local_search=true;
		}
		else
		{
			global_search=true;
		}
		//全局搜索
		if(global_search)
		{
			if(com_node<300)
			{
				HMCR=1+rand()%HMCR_max;
				PAR=PAR_max;
			}
			else
			{
				HMCR=1;
				PAR=PAR_max;
			}
		}
		//局部搜索
		else if(local_search)
		{
			if(com_node<300)
			{
				HMCR=rand()%HMCR_max;
				PAR=PAR_min;
			}
			else
			{
				HMCR=rand()%HMCR_max;
				PAR=PAR_min;
			}
		}
	}
}

bool compare(const pair<int,int> &first,const pair<int,int> &second)
{
	return first.second<second.second;
}

int the_min_pos(vector<vector<int>> &position_chaos_merge,int parallel_number_local,int server_num_local)
//返回费用最低的位置
{
	int pos=0,value=position_chaos_merge[0][server_num_local];
	for(int i=1;i<parallel_number_local;i++)
	{
		if(position_chaos_merge[i][server_num_local]<value)
		{
			value=position_chaos_merge[i][server_num_local];
			pos=i;
		}
	}
	return pos;
}

set<int> huawei_ruantiao::position_of_server(int total_node,int com_node)
{
	seconds_first= time((time_t*)NULL);
	sort_the_map();
	//服务器位置
	set<int> result;
	int min_cost,server_num;
	vector<int> costs;
	pair<set<int>,int> merge_result;
	//vector<pair<set<int>,int>> results;
	if(consumer_node<300)
	//根据消费节点数的不同，设置不同的控制参数
	{
		//并行数
		parallel_number=50;

		//变量长度与个数
		variable_length=network_node/12;
		variable_count=12;

		//扰动概率,从服务器中选择若干进行扰动		rand()%100<PAR
		PAR_max=8;		
		PAR_min=4;
		//增加或删除服务器个数
		HMCR_max=2;
		//HMCR_min=0;

		PAR=PAR_max;
		HMCR=HMCR_max;
	}
	else
	{
		//并行数
		parallel_number=50;

		//变量长度与个数
		variable_length=network_node/12;
		variable_count=12;

		//扰动概率,从服务器中选择若干进行扰动		rand()%100<PAR
		PAR_max=2;		
		PAR_min=1;
		//增加或删除服务器个数
		HMCR_max=2;
		//HMCR_min=2;

		PAR=PAR_max;
		HMCR=HMCR_max;
	}
	srand((unsigned)time(NULL));

	vector<vector<int>> position_chaos(parallel_number,vector<int>(network_node+1,0));
	vector<vector<int>> position_chaos_noise(parallel_number,vector<int>(network_node+1,0));
	vector<vector<int>> position_merge(2*parallel_number,vector<int>(network_node+1,0));

	vector<pair<int,int>> position_sort(2*parallel_number);//用于对记忆库进行排序

	//初始化和声记忆库
	for(int j=0;j<com_node;j++)
	{
		result.insert(consumers[j].num);
	}
	server_num=result.size();
	for(int i=0;i<parallel_number;i++)
	{
		for(auto iter=result.begin();iter!=result.end();iter++)
		{
			position_chaos[i][*iter]=1;
		}
	}
	min_cost=calculate_the_max_current_min_cost(position_chaos[0],0,network_node);
	for(int i=0;i<parallel_number;i++)
	{
		position_chaos[i][network_node]=min_cost;
	}

	for(int iteration_count=0;iteration_count<1000;iteration_count++)
	{
		//从和声记忆库选取值
		for(int i=0;i<parallel_number;i++)
		{
			for(int j=0;j<variable_count;j++)
			{
				for(int k=j*variable_length;k<(j+1)*variable_length;k++)
				{
					position_chaos_noise[i][k]=position_chaos[rand()%parallel_number][k];
				}
			}
			for(int k=variable_count*variable_length;k<network_node;k++)
			{
				position_chaos_noise[i][k]=position_chaos[rand()%parallel_number][k];
			}
		}
		//扰动服务器,服务器放在邻接点
		for(int i=0;i<parallel_number;i++)
		{
			int pos;
			for(int j=0;j<network_node;j++)
			{
				if(position_chaos_noise[i][j]==1)
				{
					if(rand()%100<PAR)
					{
						pos=rand()%connects[j].size();
						position_chaos_noise[i][j]=0;
						position_chaos_noise[i][connects[j][pos].end]=1;
					}
				}
			}
		}
		//添加或删除HMCR个服务器(1-server_num/network_node的概率删除，server_num/network_node的概率增加)
		for(int k=0;k<HMCR;k++)
		{
			int pos;
			double posibility=server_num/(network_node+0.0);
			for(int i=0;i<parallel_number;i++)
			{
				if((rand()%(10000+1))/(10001.0)<posibility)
				{
					while(position_chaos_noise[i][pos=rand()%network_node]==1);
					position_chaos_noise[i][pos]=1;
				}
				else
				{
					while(position_chaos_noise[i][pos=rand()%network_node]==0);
					position_chaos_noise[i][pos]=0;
				}
			}
		}
		for(int i=0;i<parallel_number;i++)
		{
			position_chaos_noise[i][network_node]=calculate_the_max_current_min_cost(position_chaos_noise[i],0,network_node);
		}
		for(int i=0;i<parallel_number;i++)
		{
			position_merge[i]=position_chaos[i];
		}
		for(int i=0;i<parallel_number;i++)
		{
			position_merge[i+parallel_number]=position_chaos_noise[i];
		}
		for(int i=0;i<2*parallel_number;i++)
		{
			position_sort[i]=make_pair(i,position_merge[i][network_node]);
		}
		sort(position_sort.begin(),position_sort.end(),compare);
		for(int i=0;i<parallel_number;i++)
		{
			position_chaos[i]=position_merge[position_sort[i].first];
		}
		if((time((time_t*)NULL)-seconds_first)>EXIT_TIME)
		{
			break;
		}
		costs.push_back(position_chaos[0][network_node]);
		global_search_or_local_search(costs,iteration_count,com_node);
		server_num=0;
		for(int i=0;i<network_node;i++)
		{
			if(position_chaos[0][i]==1)
				server_num+=1;
		}
		cout<<position_chaos[0][network_node]<<endl;
	}
	result.clear();
	for(int i=0;i<network_node;i++)
	{
		if(position_chaos[0][i]==1)
		result.insert(i);
	}
	return result;
}
