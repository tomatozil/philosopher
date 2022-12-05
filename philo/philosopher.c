/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyun <jiyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:55:28 by jiyun             #+#    #+#             */
/*   Updated: 2022/12/02 19:00:27 by jiyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosopher.h"

int	check_full(t_info *info)
{
	pthread_mutex_lock(&info->check_mutex);
	if (info->num_of_full == info->num_of_philos)
	{
		printf("%ld all philosophers are full\n", \
			get_time() - info->start_time);
		pthread_mutex_unlock(&info->check_mutex);
		return (1);
	}
	pthread_mutex_unlock(&info->check_mutex);
	return (0);
}

void	keep_an_eye_on(t_info *info, t_philosopher **philo)
{
	int	i;

	while (1)
	{
		if (check_full(info) == 1)
			return ;
		i = -1;
		while (++i < info->num_of_philos)
		{
			pthread_mutex_lock(&info->check_mutex);
			if (get_time() - (*philo)[i].last_time_eat > info->time_to_die)
			{
				info->someone_dead = YES;
				pthread_mutex_lock(&info->print_mutex);
				printf("%ld %d is dead.\n", \
				get_time() - info->start_time, (&(*philo)[i])->index);
				pthread_mutex_unlock(&info->print_mutex);
				pthread_mutex_unlock(&info->check_mutex);
				return ;
			}
			pthread_mutex_unlock(&info->check_mutex);
		}
		usleep(100);
	}
}

int	main(int ac, char **av)
{
	t_info			info;
	t_philosopher	*philo;

	if (ac != 5 && ac != 6)
		return (error_return());
	if (init_info(ac, av, &info) == 1)
		return (error_return());
	if (init_philosophers(&info, &philo) == 1)
		return (error_return());
	keep_an_eye_on(&info, &philo);
	free_all(&info, philo);
	return (0);
}
