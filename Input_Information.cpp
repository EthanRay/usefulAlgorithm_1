#include"huawei_ruantiao.h"
#include<fstream>
void huawei_ruantiao::addNode(int start, int end, int cap, int cost)
{
	connect link;
	link.end = end; link.cap = cap, link.cost = cost; link.rev =connects[end].size();link.flow=0;
	connects[start].push_back(link);
	connect emc;
	emc.end = start; emc.cap = cap; emc.cost = cost; emc.rev =connects[start].size() - 1;emc.flow=0;
	connects[end].push_back(emc);
}
bool compare_local(const pair<int,pair<int,int>> &first,const pair<int,pair<int,int>> &second)
{
	//部署费用低排在前面，部署费用相同的情况下，出边流量高排在前面
	return (first.second.first+0.0)/first.second.second<(second.second.first+0.0)/second.second.second;
}

void huawei_ruantiao::sort_the_map()
{
	int min_pos;
	connect min_e,e,middle_e;
	for(int i=0;i<network_node;i++)
	{
		for(int j=0;j<connects[i].size()-1;j++)
		{
			min_pos=j;
			min_e=connects[i][j];
			for(int k=j+1;k<connects[i].size();k++)
			{
				e=connects[i][k];
				if(e.cost<min_e.cost)
				{
					min_e=e;
					min_pos=k;
				}
			}
			middle_e=connects[i][j];
			connects[middle_e.end][middle_e.rev].rev=min_pos;
			connects[i][j]=min_e;
			connects[min_e.end][min_e.rev].rev=j;
			connects[i][min_pos]=middle_e;
		}
	}
}

bool compare(const pair<consumer,int> &a,const pair<consumer,int> &b)
{
	return a.second>b.second;
}
bool huawei_ruantiao::Input_Information()
{
	int connect_route;
	ifstream in(input_file);
	in>>network_node>>connect_route>>consumer_node;//网络结点，链路，消费节点
	int isbn,output,cost;//输入服务器类别
	int sign=0;//0的时候输入不同类别服务器，1的时候输入网络结点部署成本
	the_biggest_current_of_server=0;//服务器的最大输出流
	while(in>>isbn)
	{
		if(isbn==0&&sign==0)
			sign=1;
		else if(isbn==0&&sign==1)
			break;
		in>>output>>cost;
		if(output>the_biggest_current_of_server)
			the_biggest_current_of_server=output;
		classification_of_servers.push_back(make_pair(output,cost));
	}
	in>>cost;
	deploy_cost_of_server.push_back(cost);
	for(int i=0;i<network_node-1;i++)
	{
		in>>isbn;
		in>>cost;
		deploy_cost_of_server.push_back(cost);
	}
	//current_of_each_vertice_sorted.assign(network_node,0);
	vector<connect> empty;
	connects.assign(network_node,empty);

	int start,end,cap;
	for(int i=0;i<connect_route;i++)
	{
		in>>start>>end>>cap>>cost;
		addNode(start,end,cap,cost);
	}
	//对图的所有顶点的邻接顶点按照出边流量大小进行排序
	consumers.assign(consumer_node,0);
	for(int i=0;i<consumer_node;i++)
	{
		in>>consumers[i].isbn>>consumers[i].num>>consumers[i].need;
	}
	vector<pair<consumer,int>> consumers_sort(consumer_node);
	int total_out;
	for(int i=0;i<consumer_node;i++)//根据消费节点的出边的总流量消耗排序
	{
		consumers_sort[i].first=consumers[i];
		consumers_sort[i].second=consumers[i].need;
	}
	sort(consumers_sort.begin(),consumers_sort.end(),compare);
	for(int i=0;i<consumer_node;i++)
	{
		consumers[i]=consumers_sort[i].first;
	}
	return true;
}