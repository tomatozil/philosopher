
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
	pthread_mutex_t *fork; //fork(mutex) list
}	t_info;

typedef struct s_philosopher
{
	int left_fork;
	int right_fork;
	int status;
	long last_time_eat; //time_t -> _int64
	t_info *info;
	pthread_t thread;
}	t_philosopher;

typedef enum s_stauts
{
	EAT,
	SLEEP,
	THINK,
	DIE
}	t_status;

typedef enum s_report
{
	NONE = -1,
};

#endif
