
#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
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
	pthread_mutex_t *fork_mutex; //fork_mutex(mutex) list
	pthread_mutex_t print_mutex;
	pthread_mutex_t check_mutex;
}	t_info;

typedef struct s_philosopher
{
	int index;
	int left_fork;
	int right_fork;
	int status;
	int eat_count;
	long last_time_eat; //time_t -> _int64
	t_info *info;
	pthread_t thread;
}	t_philosopher;

typedef enum s_stauts
{
	EAT,
	SLEEP,
	THINK,
	LIVE,
	DEAD,
	FULL
}	t_status;

typedef enum s_report
{
	NONE = -1,
	NO,
	YES,
} t_report;

#endif
