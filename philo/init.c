//
// Created by jiyun on 2022/11/30.
//
#include "philosopher.h"

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

int init_mutex(t_info *info)
{
	int i;

	info->fork_mutex = malloc(sizeof(pthread_mutex_t) * info->num_of_philos);
	if (!info->fork_mutex)
		return (1);
	i = -1;
	while (++i < info->num_of_philos)
		if (pthread_mutex_init(&info->fork_mutex[i], NULL) != 0)
			return (1);
	if (pthread_mutex_init(&info->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&info->check_mutex, NULL) != 0)
		return (1);
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
	if(init_mutex(info) == 1)
		return (1);
	return (0);
}

int init_thread(t_info *info, t_philosopher **philo)
{
	int i;

	i = -1;
	while (++i < info->num_of_philos)
	{
		if (pthread_create(&(*philo)[i].thread, NULL, \
		lets_eat, &(*philo)[i]) != 0)
			return (1);
//		if (pthread_detach((*philo)[i].thread) != 0)
//			return (1);
	}
	return (0);
}

/*
philo = 배열의 주소
		*philo = 배열
				**philo = 배열의 요소
&(*philo[i])
&(*philo)[i]
 */

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
		(*philo)[i].left_fork = i;
		(*philo)[i].status = EAT;
		(*philo)[i].right_fork = i + 1;
		(*philo)[i].eat_count = 0;
		(*philo)[i].last_time_eat = get_time();
		(*philo)[i].info = info;
	}
	(*philo)[i - 1].right_fork = 0; //마지막 사람의 오른쪽 포크 == 첫 사람의 왼쪽 포크
	if (init_thread(info, philo) == 1)
		return (1);
	return (0);
}