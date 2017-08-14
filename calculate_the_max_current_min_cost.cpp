#ifndef INCLUDE
#define INCLUDE
#include"huawei_ruantiao.h"
#include<queue>
#endif
static int dist[1200];//该节点距离服务器的距离
static int _prev[1200];//记录前驱节点
static int prev_edge[1200];//记录前驱节点到达该节点所经过边的位置
static bool visited[1200];//该节点是否被访问过
static queue<int> que;

int huawei_ruantiao::calculate_one_current_min_cost(int &pos,int &current,vector<vector<connect>> &map)
{
	int costs=0,cost,flow;
	pair<int,int> Dijkstra_result;
	while(current)
	{
		Dijkstra_result=Dijkstra(pos,map,current);
		flow=Dijkstra_result.first;
		cost=Dijkstra_result.second;
		current-=flow;
		if(cost==INT_MAX)
			return INT_MAX;
		costs+=cost;
	}
	return costs;
}
int huawei_ruantiao::calculate_the_max_current_min_cost(vector<int> &position,int start,int end)
//position存储服务器的位置，start和end分别是服务器的起点和终点位置（可能有重复）
{
	map=connects;//拷贝一份网络图出来
	position_of_server_for_current.clear();
	for(int i=start;i!=end;i++)
	{
		if(position[i]==1)
			position_of_server_for_current.insert(i);
	}
	for(auto iter=position_of_server_for_current.begin();iter!=position_of_server_for_current.end();iter++)
	{
		map[*iter].push_back(connect(0,0,the_biggest_current_of_server,-1,0));
	}
	int pos,current,result,results=0;//result保存总消费

	for(int i=0;i<consumer_node;i++)//对于每一个节点，计算最小费用流，直到满足要求
	{
		pos=consumers[i].num;//消费节点位置
		current=consumers[i].need;//消费节点所需的流量
		result=calculate_one_current_min_cost(pos,current,map);
		if(result==INT_MAX)
			return INT_MAX;
		results+=result;
	}
	for(auto iter=position_of_server_for_current.begin();iter!=position_of_server_for_current.end();iter++)
	{
		if(map[*iter][map[*iter].size()-1].flow!=0)
		{
			for(auto iter1=classification_of_servers.begin();iter1!=classification_of_servers.end();iter1++)
			{
				if(map[*iter][map[*iter].size()-1].flow<=iter1->first)
				{
					results+=iter1->second;
					break;
				}
			}
		}
		results+=deploy_cost_of_server[*iter];
	}
	return results;
}
int huawei_ruantiao::calculate_the_max_current_min_cost1(vector<int> &position,int start,int end)
//position存储服务器的位置，start和end分别是服务器的起点和终点位置（可能有重复）
{
	map=connects;//拷贝一份网络图出来
	position_of_server_for_current.clear();
	for(int i=start;i!=end;i++)
	{
		position_of_server_for_current.insert(position[i]);
	}
	//-1表示超级汇
	for(auto iter=position_of_server_for_current.begin();iter!=position_of_server_for_current.end();iter++)
	{
		map[*iter].push_back(connect(0,0,the_biggest_current_of_server,-1));
	}
	int pos,current,result,results=0;//result保存总消费

	for(int i=0;i<consumer_node;i++)//对于每一个节点，计算最小费用流，直到满足要求
	{
		pos=consumers[i].num;//消费节点位置
		current=consumers[i].need;//消费节点所需的流量
		result=calculate_one_current_min_cost(pos,current,map);
		if(result==INT_MAX)
			return INT_MAX;
		results+=result;
	}
	for(auto iter=position_of_server_for_current.begin();iter!=position_of_server_for_current.end();iter++)
	{
		if(map[*iter][map[*iter].size()-1].flow!=0)
		{
			for(auto iter1=classification_of_servers.begin();iter1!=classification_of_servers.end();iter1++)
			{
				if(map[*iter][map[*iter].size()-1].flow<=iter1->first)
				{
					results+=iter1->second;
					break;
				}
			}
		}
		results+=deploy_cost_of_server[*iter];
	}
	return results;
}
pair<int,int> huawei_ruantiao::Dijkstra(int &pos,vector<vector<connect>> &map,int &current)
{
	if(map[pos][map[pos].size()-1].end==-1&&map[pos][map[pos].size()-1].cap>map[pos][map[pos].size()-1].flow)
	{
		int flow=min(current,map[pos][map[pos].size()-1].cap-map[pos][map[pos].size()-1].flow);
		map[pos][map[pos].size()-1].flow+=flow;
		return pair<int,int>(flow,0);
	}
	fill(dist,dist+network_node,INT_MAX);//该节点距离服务器的距离
	fill(_prev,_prev+network_node,-1);//记录前驱节点
	fill(prev_edge,_prev+network_node,-1);//记录前驱节点到达该节点所经过边的位置
	fill(visited,visited+network_node,false);//记录当前节点是否在队列
	dist[pos]=0;
	while(!que.empty())
		que.pop();
	que.push(pos);
	visited[pos]=true;
	_prev[pos]=-1;
	int sign=0;
	int start=pos,end,min_dist_net_work;
	while(!que.empty())
	{
		min_dist_net_work=que.front();
		que.pop();
		if(map[min_dist_net_work][map[min_dist_net_work].size()-1].end==-1&&map[min_dist_net_work][map[min_dist_net_work].size()-1].cap>map[min_dist_net_work][map[min_dist_net_work].size()-1].flow)
		//服务器输出的流量小于服务器能输出的最大流量
		{
			sign=1;
			end=min_dist_net_work;
			break;
		}
		for (int j = 0; j < map[min_dist_net_work].size(); ++j)
		{
			connect e = map[min_dist_net_work][j];
			if(e.end==-1)
				continue;
			if(visited[e.end]==true)
				continue;
			if (e.cap-e.flow>0&&dist[e.end]>dist[min_dist_net_work]+e.cost)
			{
				dist[e.end] = dist[min_dist_net_work] + e.cost;
				_prev[e.end] = min_dist_net_work;
				prev_edge[e.end]=j;
				que.push(e.end);
				visited[e.end]=true;
			}
		}
	}
	if(sign==1)
	{
		int flow=INT_MAX,pos=end,cost=0;
		while(_prev[pos]!=-1)
		{
			connect e=map[_prev[pos]][prev_edge[pos]];
			flow=min(flow,e.cap-e.flow);
			pos=_prev[pos];
		}
		flow=min(flow,current);
		flow=min(flow,map[end][map[end].size()-1].cap-map[end][map[end].size()-1].flow);
		map[end][map[end].size()-1].flow+=flow;
		pos=end;
		while(_prev[pos]!=-1)
		{
			connect &e=map[_prev[pos]][prev_edge[pos]];
			e.flow+=flow;
			cost+=flow*e.cost;
			pos=_prev[pos];
		}
		pos=end;
		while(_prev[pos]!=-1)
		{
			connect &e=map[_prev[pos]][prev_edge[pos]];
			if(e.flow>0&&map[e.end][e.rev].flow>0)
			{
				int flow_to_be_clear;
				flow_to_be_clear=min(e.flow,map[e.end][e.rev].flow);
				e.flow-=flow_to_be_clear;
				map[e.end][e.rev].flow-=flow_to_be_clear;
				cost-=flow*e.cost*2;
			}
			pos=_prev[pos];
		}
		return pair<int,int>(flow,cost);
	}
	return pair<int,int>(0,INT_MAX);
}