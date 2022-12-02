//
// Created by jiyun on 2022/11/30.
//
#include "philosopher_bonus.h"

void free_all(t_info *info, t_philosopher *philo)
{
	int i;

	i = -1;
	while (++i < info->num_of_philos)
		kill(philo[i].pid, SIGTERM);
	sem_close(info->forks_sem);
	sem_unlink("forks_sem");
	sem_close(info->print_sem);
	sem_unlink("print_sem");
	free(philo);
}