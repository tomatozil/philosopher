/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyun <jiyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:00:39 by jiyun             #+#    #+#             */
/*   Updated: 2022/12/02 19:00:45 by jiyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosopher.h"

void	delay_time(long during_time)
{
	long	target_time;
	long	cur_time;

	cur_time = get_time();
	target_time = cur_time + during_time;
	while (target_time > cur_time)
	{
		cur_time = get_time();
		usleep(250);
	}
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
