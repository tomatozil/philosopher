#include "philosopher.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_atoi(char *str)
{
	int		cnt;
	int		sign;
	long	ret;

	cnt = 0;
	sign = 1;
	ret = 0;
	while (*str == ' ' || *str == '\t' || *str == '\v' || \
			*str == '\n' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	while ('0' <= *str && *str <= '9')
	{
		ret = ret * 10 + (*str - '0');
		cnt++;
		str++;
	}
	if (*str != '\0' || cnt > 10 || cnt < 1 || \
			ret * sign > 2147483647 || ret * sign < -2147483648)
		return (-1);
	return ((int)(ret * sign));
}

int error_return(void)
{
	write(2, "error\n", 6);
	return (1);
}

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

int init_info(int ac, char **av, t_info *info)
{
	int i;

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
	i = 0;
	info->fork_mutex = malloc(sizeof(pthread_mutex_t) * info->num_of_philos);
	if (!info->fork_mutex)
		return (1);
	while (i < info->num_of_philos)
	{
		if (pthread_mutex_init(&info->fork_mutex[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int someone_dead(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->info->check_mutex);
	if (philo->info->someone_dead == YES)
	{
		pthread_mutex_unlock(&philo->info->check_mutex);
		return (YES);
	}
	pthread_mutex_unlock(&philo->info->check_mutex);
	return (NO);
}

void print_status(t_philosopher *philo)
{
	t_info	*info;

	info = philo->info;
	pthread_mutex_lock(&info->print_mutex);
	if (someone_dead(philo) == YES)
	{
		pthread_mutex_unlock(&info->print_mutex);
		return ;
	}
	printf()
}

void eating(t_philosopher *philo)
{
	t_info	*info;

	info = philo->info;
	pthread_mutex_lock(&info->fork_mutex[philo->left_fork]);
	print_status()
}

void *lets_eat(void *arg)
{
	t_philosopher *philo;

	philo = (t_philosopher *)arg;
	while (1)
	{
		if (philo->eat_count == philo->info->num_of_must_eat)
			break ;
		if (someone_dead(philo) == YES)
			break ;
		eating(philo);
		if (someone_dead(philo) == YES)
			break ;
		sleeping(philo);
		if (someone_dead(philo) == YES)
			break ;
		thinking(philo);
	}
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
		(*philo)[i].left_fork = i;
		(*philo)[i].right_fork = i + 1;
		(*philo)[i].status = i % 2; //EAT or SLEEP
		(*philo)[i].eat_count = 0;
		(*philo)[i].last_time_eat = get_time();
		(*philo)[i].info = info;
		if (pthread_create(&(*philo[i]).thread, NULL, \
		lets_eat, &(*philo[i])) != 0)
			return (1);
		if (pthread_detach((*philo)[i].thread) != 0)
			return (1);
	}
	return (0);
}

void keep_an_eye_on(t_info *info)
{
}

void free_all(t_info *info)
{
}

int main(int ac, char **av)
{
	t_info info;
	t_philosopher *philo;

	if (ac < 5)
		return (error_return());
	if (init_info(ac, av, &info) == 1)
		return (error_return());
	if (init_philosophers(&info, &philo) == 1)
		return (error_return());
	keep_an_eye_on(&info);
	free_all(&info);
	return (0);
}
