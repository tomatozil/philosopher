//
// Created by jiyun on 2022/11/30.
//
#include "philosopher_bonus.h"

void delay_time(long during_time)
{
	long target_time;
	long cur_time;

	cur_time = get_time();
	target_time = cur_time + during_time;
	while (target_time > cur_time)
	{
		cur_time = get_time();
		usleep(100);
	}
}

long get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}