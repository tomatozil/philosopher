/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyun <jiyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:01:45 by jiyun             #+#    #+#             */
/*   Updated: 2022/12/02 19:01:48 by jiyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosopher_bonus.h"

void	free_all(t_info *info, t_philosopher *philo)
{
	int	i;

	i = -1;
	while (++i < info->num_of_philos)
		kill(philo[i].pid, SIGTERM);
	sem_close(info->forks_sem);
	sem_unlink("forks_sem");
	sem_close(info->print_sem);
	sem_unlink("print_sem");
	free(philo);
}
