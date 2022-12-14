/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyun <jiyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:59:52 by jiyun             #+#    #+#             */
/*   Updated: 2022/12/02 18:59:57 by jiyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosopher.h"

void	wait_thread_join(t_info *info, t_philosopher *philo)
{
	int	i;

	i = -1;
	while (++i < info->num_of_philos)
		pthread_join(philo[i].thread, NULL);
}

void	mutex_free(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num_of_philos)
	{
		if (pthread_mutex_destroy(&info->fork_mutex[i]) != 0)
		{
			pthread_mutex_unlock(&info->fork_mutex[i]);
			pthread_mutex_destroy(&info->fork_mutex[i]);
		}
	}
	usleep(10);
	if (pthread_mutex_destroy(&info->print_mutex) != 0)
	{
		pthread_mutex_unlock(&info->print_mutex);
		pthread_mutex_destroy(&info->print_mutex);
	}
	if (pthread_mutex_destroy(&info->check_mutex) != 0)
	{
		pthread_mutex_unlock(&info->check_mutex);
		pthread_mutex_destroy(&info->check_mutex);
	}
}

void	free_all(t_info *info, t_philosopher *philo)
{
	if (philo == NULL)
	{
		mutex_free(info);
		free(info->fork_mutex);
	}
	else
	{
		if (info->num_of_philos != 1)
			wait_thread_join(info, philo);
		mutex_free(info);
		if (info->num_of_philos == 1)
			wait_thread_join(info, philo);
		free(info->fork_mutex);
		free(philo);
	}
}
