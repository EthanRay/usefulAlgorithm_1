#include "huawei_ruantiao.h"
int huawei_ruantiao::huaweiruantiao_main()
{
	Input_Information();
	the_last_result=position_of_server(network_node,consumer_node);
	results=out_put_the_result();
	return 0;
}