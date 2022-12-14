/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyun <jiyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:02:07 by jiyun             #+#    #+#             */
/*   Updated: 2022/12/02 19:02:10 by jiyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosopher_bonus.h"

void	keep_an_eye_on(t_info *info, t_philosopher **philo)
{
	int	i;
	int	status;

	while (1)
	{
		waitpid(-1, &status, 0);
		if (status >> 8 == DEAD)
		{
			info->someone_dead = YES;
			i = -1;
			while (++i < info->num_of_philos)
				kill((*philo)[i].pid, SIGTERM);
			return ;
		}
		else if (status >> 8 == FULL)
		{
			sem_post(info->check_sem);
			info->num_of_full++;
			if (info->num_of_full == info->num_of_philos)
				break ;
		}
	}
	printf("%ld all philosophers full\n", get_time() - info->start_time);
}

int	main(int ac, char **av)
{
	t_info			info;
	t_philosopher	*philo;

	if (ac != 5 && ac != 6)
		return (error_return());
	if (init_info(ac, av, &info) == 1)
		return (error_return());
	if (init_philosophers(&info, &philo) == 1)
		return (error_return());
	keep_an_eye_on(&info, &philo);
	free_all(&info, philo);
	return (0);
}
