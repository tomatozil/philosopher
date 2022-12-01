//
// Created by jiyun on 2022/11/30.
//
#include "philosopher.h"

void eating(t_philosopher *philo)
{
	t_info	*info;

	info = philo->info;
	pthread_mutex_lock(&info->fork_mutex[philo->left_fork]);
	print_status(philo, "has taken a left fork\n");
	pthread_mutex_lock(&info->fork_mutex[philo->right_fork]);
	print_status(philo, "has taken a right fork\n");
	print_status(philo, "is eating\n");
	philo->last_time_eat = get_time();
	delay_time(info->time_to_eat);
	philo->eat_count++;
	pthread_mutex_lock(&info->check_mutex);
	if (philo->eat_count == info->num_of_must_eat)
	{
		philo->status = FULL;
		info->num_of_full++;
	}
	else
		philo->status = SLEEP;
	pthread_mutex_unlock(&info->check_mutex);
	pthread_mutex_unlock(&info->fork_mutex[philo->right_fork]);
	pthread_mutex_unlock(&info->fork_mutex[philo->left_fork]);
}

void sleeping(t_philosopher *philo)
{
	print_status(philo, "is sleeping\n");
	delay_time(philo->info->time_to_sleep);
	philo->status = THINK;
}

void thinking(t_philosopher *philo)
{
	print_status(philo, "is thinking\n");
	philo->status = EAT;
}

void *lets_eat(void *arg)
{
	t_philosopher *philo;
	t_info *info;

	philo = (t_philosopher *)arg;
	info = philo->info;
	if (philo->index % 2 == 0)
		delay_time(info->time_to_eat - 10);
	while (1)
	{
		if (check_someone_dead(info) == 1)
			break ;
		if (philo->status == EAT)
			eating(philo);
		else if (philo->status == SLEEP)
			sleeping(philo);
		else if (philo->status == THINK)
			thinking(philo);
		else if (philo->status == FULL || philo->status == DEAD)
			break ;
	}
	return (NULL);
}