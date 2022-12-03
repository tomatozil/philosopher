/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyun <jiyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:00:49 by jiyun             #+#    #+#             */
/*   Updated: 2022/12/02 19:00:52 by jiyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosopher.h"

int	ft_atoi(char *str)
{
	int		cnt;
	int		sign;
	long	ret;

	cnt = 0;
	sign = 1;
	ret = 0;
	while (*str == ' ' || *str == '\t' || *str == '\v' || \
			*str == '\n' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	while ('0' <= *str && *str <= '9')
	{
		ret = ret * 10 + (*str - '0');
		cnt++;
		str++;
	}
	if (*str != '\0' || cnt > 10 || cnt < 1 || \
			ret * sign > 2147483647 || ret * sign < -2147483648)
		return (-1);
	return ((int)(ret * sign));
}

int	check_someone_dead(t_info *info)
{
	pthread_mutex_lock(&info->check_mutex);
	if (info->someone_dead == YES)
	{
		pthread_mutex_unlock(&info->check_mutex);
		return (1);
	}
	pthread_mutex_unlock(&info->check_mutex);
	return (0);
}

void	print_status(t_philosopher *philo, char *str)
{
	t_info	*info;
	long	cur_timestamp;

	info = philo->info;
	cur_timestamp = get_time() - info->start_time;
	pthread_mutex_lock(&info->check_mutex);
	pthread_mutex_lock(&info->print_mutex);
	if (info->someone_dead == YES)
	{
		pthread_mutex_unlock(&info->print_mutex);
		pthread_mutex_unlock(&info->check_mutex);
		return ;
	}
	printf("%ld %d %s", cur_timestamp, philo->index, str);
	pthread_mutex_unlock(&info->print_mutex);
	pthread_mutex_unlock(&info->check_mutex);
}

int	error_return(void)
{
	write(2, "error\n", 6);
	return (1);
}
