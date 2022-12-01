
#ifndef PHILOSOPHER_BONUS_H
# define PHILOSOPHER_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <pthread.h>

typedef struct s_info
{
	int num_of_philos;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int num_of_must_eat;
	int someone_dead;
	int num_of_full;
	long start_time;
	sem_t *forks_sem; //fork_mutex(mutex) list
//	sem_t print_mutex;
//	sem_t check_mutex    ;
}	t_info;

typedef struct s_philosopher
{
	int index;
	int status;
	int eat_count;
	long last_time_eat; //time_t -> _int64
	pid_t pid;
	t_info *info;
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
} t_report;

/* init_bonus.c */
int init_info(int ac, char **av, t_info *info);
int init_philosophers(t_info *info, t_philosopher **philo);

/* lets_eat_bonus.c */
int lets_eat(t_philosopher *philo);

/* time_bonus.c */
void delay_time(long during_time);
long get_time(void);

/* utils_bonus.c */
int	ft_atoi(char *str);
void *check_dead(void *arg);
void print_status(t_philosopher *philo, char *str);
int error_return(void);

/* free_bonus.c */
void free_all(t_info *info, t_philosopher *philo);

#endif
