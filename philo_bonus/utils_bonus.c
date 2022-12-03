/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyun <jiyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:02:28 by jiyun             #+#    #+#             */
/*   Updated: 2022/12/02 19:02:31 by jiyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosopher_bonus.h"

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

void	*check_dead(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (1)
	{
		sem_wait(philo->info->check_sem);
		if (get_time() - philo->last_time_eat > philo->info->time_to_die)
		{
			sem_wait(philo->info->print_sem);
			printf("%ld %d is dead.\n", \
			get_time() - philo->info->start_time, philo->index);
			exit(DEAD);
		}
		sem_post(philo->info->check_sem);
	}
}

/* print semaphore 필요할까나? -> 필요하다! */
void	print_status(t_philosopher *philo, char *str)
{
	t_info	*info;
	long	cur_timestamp;

	info = philo->info;
	sem_wait(info->print_sem);
	cur_timestamp = get_time() - info->start_time;
	printf("%ld %d %s", cur_timestamp, philo->index, str);
	sem_post(info->print_sem);
}

int	error_return(void)
{
	write(2, "error\n", 6);
	return (1);
}
