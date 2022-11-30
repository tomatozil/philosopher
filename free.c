//
// Created by jiyun on 2022/11/30.
//
#include "philosopher.h"

void wait_thread_join(t_info *info, t_philosopher *philo)
{
	int	i;

	i = -1;
	while (++i < info->num_of_philos)
		pthread_join(philo[i].thread, NULL);
}

void free_all(t_info *info, t_philosopher *philo)
{
	int	i;

	i = -1;
	wait_thread_join(info, philo);
	while (++i < info->num_of_philos)
	{
		if (pthread_mutex_destroy(&info->fork_mutex[i]) != 0)
		{
			pthread_mutex_unlock(&info->fork_mutex[i]);
			pthread_mutex_destroy(&info->fork_mutex[i]);
		}
	}
	if (pthread_mutex_destroy(&info->check_mutex) != 0)
	{
		pthread_mutex_unlock(&info->check_mutex);
		pthread_mutex_destroy(&info->check_mutex);
	}
	if (pthread_mutex_destroy(&info->print_mutex) != 0)
	{
		pthread_mutex_unlock(&info->print_mutex);
		pthread_mutex_destroy(&info->print_mutex);
	}
	free(info->fork_mutex);
	free(philo);
}