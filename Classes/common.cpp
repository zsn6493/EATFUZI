#include "common.h"
USING_NS_CC;

void initRandSeed()
{
	//��������ƹ���
	struct timeval now;
	gettimeofday(&now, NULL);
	//��ʼ���������
	//timeval�Ǹ��ṹ�壬���������������һ��������Ϊ��λ�ģ�һ������΢��Ϊ��λ��
	unsigned rand_seed = (unsigned)(now.tv_sec * 1000 + now.tv_usec / 1000);    //��ת��Ϊ����
	srand(rand_seed);
}