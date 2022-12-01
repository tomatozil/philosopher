//
// Created by jiyun on 2022/11/30.
//
#include "philosopher_bonus.h"

int check_info(t_info *info)
{
	if (info->num_of_philos < 0 || info->time_to_die < 0 || \
	info->time_to_eat < 0 || info->time_to_sleep < 0)
		return (1);
	if (info->num_of_must_eat != NONE)
		if (info->time_to_sleep < 0)
			return (1);
	return (0);
}

int init_sem(t_info *info)
{
	info->forks_sem = sem_open("forks_sem", O_CREAT | O_EXCL, 0664, (unsigned int)info->num_of_philos);
	if (info->forks_sem == SEM_FAILED)
	{
		sem_unlink("forks_sem");
		return (1);
	}
	return (0);
}

int init_info(int ac, char **av, t_info *info)
{
	info->num_of_philos = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		info->num_of_must_eat = ft_atoi(av[5]);
	else
		info->num_of_must_eat = NONE;
	if (check_info(info) == 1)
		return (1);
	info->someone_dead = NO;
	info->num_of_full = 0;
	info->start_time = get_time();
	if (init_sem(info) == 1)
		return (1);
	return (0);
}

int init_process(t_info *info, t_philosopher **philo)
{
	int i;

	i = -1;
	while (++i < info->num_of_philos)
	{
		(*philo)[i].pid = fork();
		if ((*philo)[i].pid == 0)
			lets_eat(&(*philo)[i]);
		else if ((*philo)[i].pid < 0)
			return (1);
	}
	return (0);
}

int init_philosophers(t_info *info, t_philosopher **philo)
{
	int i;

	*philo = malloc(sizeof(t_philosopher) * info->num_of_philos);
	if (!*philo)
		return (1);
	i = -1;
	while (++i < info->num_of_philos)
	{
		(*philo)[i].index = i + 1;
		(*philo)[i].status = EAT;
		(*philo)[i].eat_count = 0;
		(*philo)[i].last_time_eat = get_time();
		(*philo)[i].info = info;
	}
	if (init_process(info, philo) == 1)
		return (1);
	return (0);
}