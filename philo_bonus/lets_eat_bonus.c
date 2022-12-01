//
// Created by jiyun on 2022/11/30.
//
#include "philosopher_bonus.h"

void eating(t_philosopher *philo)
{
	t_info	*info;

	info = philo->info;
	sem_wait(info->forks_sem);
	print_status(philo, "has taken a left fork\n");
	sem_wait(info->forks_sem);
	print_status(philo, "has taken a right fork\n");
	print_status(philo, "is eating\n");
	philo->last_time_eat = get_time();
	delay_time(info->time_to_eat);
	philo->eat_count++;
	if (philo->eat_count == info->num_of_must_eat)
	{
		philo->status = FULL;
		info->num_of_full++;
	}
	else
		philo->status = SLEEP;
	sem_post(info->forks_sem);
	sem_post(info->forks_sem);
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

int lets_eat(t_philosopher *philo)
{
	t_info *info;
	pthread_t thread;

	info = philo->info;
	if (pthread_create(&thread, NULL, check_dead, philo) != 0)
		exit (1);
	if (philo->index % 2 == 0)
		delay_time(info->time_to_eat - 10);
	while (1)
	{
		if (philo->status == EAT)
			eating(philo);
		else if (philo->status == SLEEP)
			sleeping(philo);
		else if (philo->status == THINK)
			thinking(philo);
		else if (philo->status == FULL)
			exit(FULL) ;
	}
}