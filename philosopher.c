#include "philosopher.h"

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
	i = 0;
	while (i < info->num_of_philos)
	{
		if (pthread_mutex_init(&info->fork[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int init_philosophers(t_info *info, t_philosopher **philosophers)
{
	int i;

	i = 0;
	while (i < info->num_of_philos)
	{
		if (pthread_create(&(*philosophers[i]->thread), NULL, \
		lets_eat, &(*philosophers[i])) != 0)
			return (1);
		(*philosophers)->index = i + 1;
		i++;
	}
	return (0);
}

void lets_eat(void *arg)
{
	t_philosopher *philosopher;

	philosopher = (t_philosopher *)arg;

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
	t_philosopher *philosophers;

	if (ac < 5)
		return (error_return());
	if (init_info(ac, av, &info) == 1)
		return (error_return());
	if (init_philosophers(&info, &philosophers) == 1)
		return (error_return());
	keep_an_eye_on(&info);
	free_all(&info);
	return (0);
}
