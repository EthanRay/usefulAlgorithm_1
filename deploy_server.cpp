#include "huawei_ruantiao.h"
#include<vector>
#include<string>
#include<fstream>
void main()
{
	class huawei_ruantiao object;
	object.input_file="case1.txt";
	object.huaweiruantiao_main();
	//输出结果
	vector<vector<int>> output;
	for(auto iter=object.results.begin();iter!=object.results.end();iter++)
		for(auto iter1=iter->begin();iter1!=iter->end();iter1++)
			output.push_back(*iter1);
	ofstream out("case10.txt");//覆盖输出
	out<<output.size()<<endl;
	for(auto iter=output.begin();iter!=output.end();iter++)
	{
		for(auto iter1=iter->begin();iter1!=iter->end();iter1++)
		{
			if(iter1!=iter->end()-1)
				out<<*iter1<<" ";
			else
				out<<*iter1<<endl;
		}
	}
}