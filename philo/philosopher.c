#include "philosopher.h"

void	keep_an_eye_on(t_info *info, t_philosopher **philo)
{
	int	i;

	while (1)
	{
		pthread_mutex_lock(&info->check_mutex);
		if (info->num_of_full == info->num_of_philos)
		{
			printf("%ld all philosophers are full\n", get_time() - info->start_time);
			pthread_mutex_unlock(&info->check_mutex);
			return ;
		}
		pthread_mutex_unlock(&info->check_mutex);
		i = -1;
		while (++i < info->num_of_philos)
		{
			if ((*philo)[i].status != FULL && get_time() - (*philo)[i].last_time_eat > info->time_to_die)
			{
				pthread_mutex_lock(&info->check_mutex);
				(*philo)[i].status = DEAD;
				info->someone_dead = YES;
				printf("%ld %d is dead.\n", get_time() - info->start_time, (&(*philo)[i])->index);
				pthread_mutex_unlock(&info->check_mutex);
				return ;
			}
		}
	}
}

int main(int ac, char **av)
{
	t_info info;
	t_philosopher *philo;

//	int ac = 6;
//	char *av[6] = {"a.out", "4", "450", "200", "200", "2"};
//	int ac = 5;
//	char *av[6] = {"a.out", "199", "410", "200", "200"};
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
