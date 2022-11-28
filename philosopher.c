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
	info->num_of_full = 0;
	info->start_time = get_time();
	info->fork_mutex = malloc(sizeof(pthread_mutex_t) * info->num_of_philos);
	if (!info->fork_mutex)
		return (1);
	i = -1;
	while (++i < info->num_of_philos)
		if (pthread_mutex_init(&info->fork_mutex[i], NULL) != 0)
			return (1);
	return (0);
}

/* 이거 구림 */
int check_someone_dead(t_info *info)
{
	pthread_mutex_lock(&info->check_mutex);
	if (info->someone_dead == YES)
	{
		pthread_mutex_unlock(&info->check_mutex);
		return (1);
	}
	pthread_mutex_unlock(&info->check_mutex);
	return (0);
}

void check_philo_full(t_info *info, t_philosopher *philo)
{
	pthread_mutex_lock(&info->check_mutex);
	if (philo->eat_count == info->must_eat_count)
		info->num_of_full++;
	pthread_mutex_unlock(&info->check_mutex);
}

void print_status(t_philosopher *philo, char *str)
{
	t_info	*info;
	long cur_timestamp;

	info = philo->info;
	cur_timestamp = get_time() - info->start_time;
	pthread_mutex_lock(&info->print_mutex);
	if (check_someone_dead(info) == 1)
	{
		pthread_mutex_unlock(&info->print_mutex);
		return ;
	}
	printf("%ld %d %s", cur_timestamp, philo->index, str);
	pthread_mutex_unlock(&info->print_mutex);
}

void delay_time(int during_time)
{
	long target_time;
	long cur_time;

	cur_time = get_time();
	target_time = cur_time + during_time;
	while (target_time > cur_time)
		usleep(100);
}

void eating(t_philosopher *philo)
{
	t_info	*info;

	info = philo->info;
	pthread_mutex_lock(&info->fork_mutex[philo->left_fork]);
	print_status(philo, "has taken a fork\n");
	pthread_mutex_lock(&info->fork_mutex[philo->right_fork]);
	print_status(philo, "has taken a fork\n");
	print_status(philo, "is eating\n");
	delay_time(info->time_to_eat);
	philo->last_time_eat = get_time();
	philo->eat_count++;
	philo->status = SLEEP;
	pthread_mutex_unlock(&info->fork_mutex[philo->left_fork]);
	pthread_mutex_unlock(&info->fork_mutex[philo->right_fork]);
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
	while (1)
	{
		if (philo->eat_count == info->num_of_must_eat)
			break ;
		if (check_someone_dead(info) == 1)
			break ;
		eating(philo);
		if (check_someone_dead(info) == 1)
			break ;
		sleeping(philo);
		if (check_someone_dead(info) == 1)
			break ;
		thinking(philo);
	}
	check_philo_full(info, philo);
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
		(*philo)[i].status = LIVE;
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

void keep_an_eye_on(t_info *info, t_philosopher **philo)
{
	int i;

	while (1)
	{
		// 다들 먹을만큼 먹었는지 검사
		pthread_mutex_lock(&info->check_mutex);
		if (info->num_of_full == info->num_of_philos)
		{
			printf("all philosophers are full\n")
			pthread_mutex_unlock(&info->check_mutex);
			break ;
		}
		pthread_mutex_unlock(&info->check_mutex);
		// 죽은 사람 있는지 검사
		i = -1;
		while (++i < info->num_of_philos)
		{
			if (get_time() - (*philo)[i].last_time_eat > info->time_to_die)
			{
				pthread_mutex_lock(&info->check_mutex);
				(*philo)[i].status = DEAD;
				info->someone_dead = YES;
				pthread_mutex_unlock(&info->check_mutex);
				print_status(&(*philo)[i], "is dead.\n");
				// 포크를 아직 갖고있을 수 있으니까 내려놔? -> 놉 뒤에서 free 다 해줄건디 뭐
				return;
			}
		}
	}
}

void free_all(t_info *info, t_philosopher *philos)
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
	free(info->fork_mutex);
	free(philos);
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
	keep_an_eye_on(&info, &philo);
	free_all(&info, philo);
	return (0);
}
