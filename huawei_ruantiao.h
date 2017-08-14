#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<algorithm>
#include<time.h>
#define MAXVEX 1000
#define INT_MAX 2147483647
using namespace std;
struct node
{
	int new_work_pos,distance;
	node(int _new_work_pos=0,int _distance=0)
	{
		new_work_pos=_new_work_pos;
		distance=_distance;
	}
};
struct connect
{
	int flow,cost,cap,end,rev;//�����յ�
	connect(int _flow=0,int _cost=0,int _cap=0,int _end=0,int _rev=0)
	{
		flow=_flow;cost= _cost;cap= _cap;end=_end;rev=_rev;
	}
};
struct consumer
{
	int num,need,isbn;//���ѽڵ����ӵ������㣬���ѽڵ��������Ƶ
	consumer(int _num=0,int _need=0)
	{
		num=_num;
		need=_need;
		isbn=-1;
	}
};
class huawei_ruantiao
{
public:
	int huaweiruantiao_main();
	int calculate_the_max_current_min_cost(vector<int> &position,int start,int end);
	int calculate_the_max_current_min_cost1(vector<int> &position,int start,int end);
	int calculate_one_current_min_cost(int &pos,int &current,vector<vector<connect>> &map);
	//position�洢��������λ�ã�start��end�ֱ��Ƿ������������յ�λ�ã��������ظ���
	set<int> position_of_server(int total_node,int com_node);
	vector<vector<vector<int>>> out_put_the_result();
	bool Input_Information();
	string input_file;
	void addNode(int start, int end, int cap, int cost);
	void sort_the_map();
	vector<vector<vector<int>>> results;//���������
	pair<set<int>,int> merge_position_of_server(const set<int> &result,int min_cost);
	pair<int,int> Dijkstra(int &pos,vector<vector<connect>> &map,int &current);
	pair<int,int> Dijkstra1(int &pos,vector<vector<connect>> &map,int &current);
private:
	int network_node;//��������
	int server_number_current;
	//vector<int> current_of_each_vertice_sorted;//������������ߵ���������
	vector<vector<connect>> connects,map;//�洢ͼ���ڽӱ�
	set<int> position_of_server_for_current;//�洢���еķ�����λ��
	vector<consumer> consumers;//�洢������
	//vector<pair<int,int>> cost_of_consumers;
	vector<pair<int,int>> classification_of_servers;//�洢���������
	int the_biggest_current_of_server;//����������������
	vector<int> deploy_cost_of_server;//�����㲿��ɱ�
	int consumer_node;//���ѽڵ���
	set<int> the_last_result;//�洢�����������λ��
};
