/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyun <jiyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:00:07 by jiyun             #+#    #+#             */
/*   Updated: 2022/12/02 19:00:11 by jiyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosopher.h"

int	check_info(t_info *info)
{
	if (info->num_of_philos <= 0 || info->time_to_die < 0 || \
	info->time_to_eat < 0 || info->time_to_sleep < 0 || info->num_of_must_eat <= 0)
		return (1);
	return (0);
}

int	init_mutex(t_info *info)
{
	int	i;
	int	status;

	status = YES;
	info->fork_mutex = malloc(sizeof(pthread_mutex_t) * info->num_of_philos);
	if (!info->fork_mutex)
		return (1);
	i = -1;
	while (++i < info->num_of_philos)
		if (pthread_mutex_init(&info->fork_mutex[i], NULL) != 0)
			status = NO;
	if (pthread_mutex_init(&info->print_mutex, NULL) != 0)
		status = NO;
	if (pthread_mutex_init(&info->check_mutex, NULL) != 0)
		status = NO;
	if (status == NO)
	{
		free_all(info, NULL);
		return (1);
	}
	return (0);
}

int	init_info(int ac, char **av, t_info *info)
{
	info->num_of_philos = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		info->num_of_must_eat = ft_atoi(av[5]);
	if (check_info(info) == 1)
		return (1);
	if (ac == 5)
		info->num_of_must_eat = NONE;
	info->someone_dead = NO;
	info->num_of_full = 0;
	info->start_time = get_time();
	if (init_mutex(info) == 1)
		return (1);
	return (0);
}

int	init_thread(t_info *info, t_philosopher **philo)
{
	int	i;

	i = -1;
	while (++i < info->num_of_philos)
	{
		if (pthread_create(&(*philo)[i].thread, NULL, \
		lets_eat, &(*philo)[i]) != 0)
		{
			free_all(info, *philo);
			return (1);
		}
	}
	return (0);
}

int	init_philosophers(t_info *info, t_philosopher **philo)
{
	int	i;

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
	(*philo)[i - 1].right_fork = 0;
	if (init_thread(info, philo) == 1)
		return (1);
	return (0);
}
