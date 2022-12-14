/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyun <jiyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:01:52 by jiyun             #+#    #+#             */
/*   Updated: 2022/12/02 19:01:56 by jiyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosopher_bonus.h"

int	check_info(t_info *info)
{
	if (info->num_of_philos <= 0 || info->time_to_die < 0 || \
	info->time_to_eat < 0 || info->time_to_sleep < 0 || info->num_of_must_eat <= 0)
		return (1);
	return (0);
}

void	init_sem(t_info *info)
{
	info->forks_sem = sem_open("forks_sem", O_CREAT | O_EXCL, \
	0644, (unsigned int)info->num_of_philos);
	if (info->forks_sem == SEM_FAILED)
	{
		sem_unlink("forks_sem");
		info->forks_sem = sem_open("forks_sem", O_CREAT | O_EXCL, \
		0644, (unsigned int)info->num_of_philos);
	}
	info->print_sem = sem_open("print_sem", O_CREAT | O_EXCL, \
	0644, (unsigned int)1);
	if (info->print_sem == SEM_FAILED)
	{
		sem_unlink("print_sem");
		info->print_sem = sem_open("print_sem", O_CREAT | O_EXCL, \
		0644, (unsigned int)1);
	}
	info->check_sem = sem_open("check_sem", O_CREAT | O_EXCL, \
	0644, (unsigned int)1);
	if (info->check_sem == SEM_FAILED)
	{
		sem_unlink("check_sem");
		info->check_sem = sem_open("check_sem", O_CREAT | O_EXCL, \
		0644, (unsigned int)1);
	}
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
	init_sem(info);
	return (0);
}

int	init_process(t_info *info, t_philosopher **philo)
{
	int	i;

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
		(*philo)[i].status = EAT;
		(*philo)[i].eat_count = 0;
		(*philo)[i].last_time_eat = get_time();
		(*philo)[i].info = info;
	}
	if (init_process(info, philo) == 1)
	{
		free_all(info, *philo);
		return (1);
	}
	return (0);
}
