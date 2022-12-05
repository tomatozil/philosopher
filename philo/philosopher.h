/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyun <jiyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:00:31 by jiyun             #+#    #+#             */
/*   Updated: 2022/12/02 19:00:34 by jiyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_info
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_must_eat;
	int				someone_dead;
	int				num_of_full;
	long			start_time;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	check_mutex;
}	t_info;

typedef struct s_philosopher
{
	int			index;
	int			left_fork;
	int			right_fork;
	int			status;
	int			eat_count;
	long		last_time_eat;
	t_info		*info;
	pthread_t	thread;
}	t_philosopher;

typedef enum e_stauts
{
	EAT,
	SLEEP,
	THINK,
	DEAD,
	FULL
}	t_status;

typedef enum e_report
{
	NONE = -1,
	NO,
	YES,
}	t_report;

/* init.c */
int		init_info(int ac, char **av, t_info *info);
int		init_philosophers(t_info *info, t_philosopher **philo);

/* lets_eat.c */
void	*lets_eat(void *arg);

/* time.c */
void	delay_time(long during_time);
long	get_time(void);

/* utils.c */
int		ft_atoi(char *str);
int		check_someone_dead(t_info *info);
void	print_status(t_philosopher *philo, char *str);
int		error_return(void);

/* free.c */
void	free_all(t_info *info, t_philosopher *philo);

#endif
