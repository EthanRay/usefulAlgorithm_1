#include "huawei_ruantiao.h"
#include<algorithm>
#include<queue>
struct compare
{
	bool operator()(const node &a,const node &b)
	{
		return a.distance>b.distance;
	}
};
bool Dijkstra_path(int start,vector<vector<connect>> &map,set<int> &the_last_result,vector<int> &path,vector<pair<int,int>> &path_copy,vector<vector<int>> &paths,int flow,vector<pair<int,int>> &the_last_server_output);
int calculate_one_current_min_cost_output(int &pos,int &current,vector<vector<connect>> &map,set<int> &position_of_server,vector<int> &the_last_server_output,int the_last_biggest_current_of_server);
vector<vector<vector<int>>> huawei_ruantiao::out_put_the_result()
{
	int pos,current;
	vector<int> the_last_server_deploy(network_node,0);
	for(auto iter=the_last_result.begin();iter!=the_last_result.end();iter++)
	{
		the_last_server_deploy[*iter]=1;
	}
	calculate_the_max_current_min_cost(the_last_server_deploy,0,network_node);
	vector<vector<connect>> map1=map;
	vector<vector<vector<int>>> all_paths;//存储所有消费节点的总路径
	vector<vector<int>> paths;//存储每一个消费节点的流量路径
	vector<int> path;
	vector<pair<int,int>> path_copy;
	vector<int> the_last_server_output;
	the_last_server_output.assign(network_node,0);//记录服务器的输出流量
	for(auto iter=the_last_result.begin();iter!=the_last_result.end();iter++)
	{
		the_last_server_output[*iter]=map1[*iter][map1[*iter].size()-1].flow;
	}
	vector<pair<int,int>> the_last_server_output_and_grade(network_node,make_pair(0,0));

	for(auto iter=the_last_result.begin();iter!=the_last_result.end();iter++)
	{
		if(the_last_server_output[*iter]!=0)
		{
			for(int j=0;j<classification_of_servers.size();j++)
			{
				if(the_last_server_output[*iter]<=classification_of_servers[j].first)
				{
					the_last_server_output_and_grade[*iter]=(make_pair(the_last_server_output[*iter],j));
					break;
				}
			}
		}
	}
	//从map1图中去除超级汇
	for(auto iter=the_last_result.begin();iter!=the_last_result.end();iter++)
	{
		map1[*iter].pop_back();
	}
	//对于每一个消费节点，计算最小费用流，直到满足要求
	for(auto iter=consumers.begin();iter!=consumers.end();iter++)
	{
		path.clear();
		path_copy.clear();
		path.push_back(iter->isbn);
		if(Dijkstra_path(iter->num,map1,the_last_result,path,path_copy,paths,iter->need,the_last_server_output_and_grade))
		{
			all_paths.push_back(paths);
			paths.clear();
		}
		else
		{
			cout<<"error"<<endl;
			break;
		}
	}
	int sign=0;
	for(int i=0;i<map1.size();i++)
		for(int j=0;j<map1[i].size();j++)
			if(map1[i][j].flow!=0)
			{
				sign=1;
			}
	cout<<sign<<endl;
	while(1);
	return all_paths;
}

bool Dijkstra_path(int start,vector<vector<connect>> &map,set<int> &the_last_result,vector<int> &path,vector<pair<int,int>> &path_copy,vector<vector<int>> &paths,int flow,vector<pair<int,int>> &the_last_server_output_and_grade)
{
	path.push_back(start);
	if(the_last_result.count(start)==1&&the_last_server_output_and_grade[start].first>0)
	{
		int flow_local=min(flow,the_last_server_output_and_grade[start].first);
		the_last_server_output_and_grade[start].first-=flow_local;
		for(auto iter=path_copy.begin();iter!=path_copy.end();iter++)
			map[iter->first][iter->second].flow-=flow_local;
		vector<int> middle_path;
		middle_path=path;
		reverse(middle_path.begin(),middle_path.end());
		middle_path.push_back(flow_local);
		middle_path.push_back(the_last_server_output_and_grade[start].second);
		paths.push_back(middle_path);
		if(flow==flow_local)
		{
			path.pop_back();
			return true;
		}
		flow-=flow_local;
	}
	for(int i=0;i<map[start].size();i++) 
	{
		if(map[start][i].flow>0)
		{
			path_copy.push_back(make_pair(start,i));
			int path_flow=min(map[start][i].flow,flow);//分流
			if(!Dijkstra_path(map[start][i].end,map,the_last_result,path,path_copy,paths,min(map[start][i].flow,flow),the_last_server_output_and_grade))
			{
				path_copy.pop_back();
				path.pop_back();
				return false;
			}
			flow-=path_flow;
			path_copy.pop_back();
			if(flow==0)
			{
				path.pop_back();
				return true;
			}
		}
	}
	path.pop_back();
	return false;
}