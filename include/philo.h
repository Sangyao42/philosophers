/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:26:02 by sawang            #+#    #+#             */
/*   Updated: 2023/04/25 22:42:17 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>

/**
 * mutex for print
 * mutex for left fork and right fork
 * mutex for dead or not
 * mutex for eat count?
*/

// typedef struct s_input
// {
// 	unsigned int	num_of_philos;
// 	unsigned int	time_to_die;
// 	unsigned int	time_to_eat;
// 	unsigned int	time_to_sleep;
// 	unsigned int	num_of_must_eat;
// }				t_input;

typedef unsigned long	t_milliseconds;

typedef enum e_philo_status
{
	THINKING,
	EATING,
	SLEEPING,
	// FORKING,?
	DIED
}				t_philo_status;

struct s_input
{
	unsigned int		num_of_philos;
	t_milliseconds		time_to_die;
	t_milliseconds		time_to_eat;
	t_milliseconds		time_to_sleep;
	unsigned int		num_of_must_eat;
};

struct s_philo
{
	unsigned int	id;
	pthread_mutex_t	*mutex_l_fork;
	pthread_mutex_t	*mutex_r_fork;
	// status
	t_milliseconds	start_time;
	t_philo_status	status;
	t_milliseconds	last_eat;
	unsigned int	eat_cnt;
	struct s_table	*table;
};

struct s_philo_holding
{
	struct s_philo	*philos;
	pthread_t		*philo_thrs;
	pthread_mutex_t	*mutex_forks;
};

typedef enum e_start_status
{
	UNINITIALIZED_START,
	INITIALIZED_START,
	NOT_STARTED,
	START
}			t_start_status;

typedef enum e_kill_status
{
	UNINITIALIZED_KILL,
	INITIALIZED_KILL,
	ALIVE,
	KILL
}			t_kill_status;

struct s_traffic_light
{
	pthread_mutex_t	mutex_start;
	t_start_status	start;
	pthread_mutex_t	mutex_kill;
	t_kill_status	kill;
};

struct s_table
{
	struct s_input			input;
	struct s_philo_holding	philo_holding;
	pthread_mutex_t			mutex_print;
	pthread_t				death;
	struct s_traffic_light	traffic_light;
};

/**
 * input
*/
bool			set_input(struct s_table *table, int argc, char *argv[]);

/**
 * init
*/
bool			set_table(struct s_table *table, int argc, char *argv[]);

/**
 * death
*/
void			*death_routine(struct s_table *table);

/**
 * philosophers
*/
bool			philo_dining_simulation(struct s_table *table);
void			philo_activity(struct s_philo *philo);
void			philo_threads_join(struct s_table *table, int i);
/**
 * lonly philosopher
*/
int				lonely_philo_simulator(struct s_table *table);

/**
 * error_handler
*/
void			mutex_destroy_and_free(struct s_table *table, \
				unsigned int philo_cnt);

/**
 * timer
*/
t_milliseconds	time_now(void);
t_milliseconds	time_passed(t_milliseconds start_time);
void			sleep_better(t_milliseconds should_sleep);

/**
 * printer
*/
void			print_status(struct s_philo *philo, char *doing);

/**
 * utils
*/
void			*ft_calloc(size_t count, size_t size);
unsigned long	philo_atoi(const char *str);

#endif
