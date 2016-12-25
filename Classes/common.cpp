#include "common.h"
USING_NS_CC;

void initRandSeed()
{
	//随机数复制过程
	struct timeval now;
	gettimeofday(&now, NULL);
	//初始化随机种子
	//timeval是个结构体，里边有俩个变量，一个是以秒为单位的，一个是以微妙为单位的
	unsigned rand_seed = (unsigned)(now.tv_sec * 1000 + now.tv_usec / 1000);    //都转化为毫秒
	srand(rand_seed);
}