/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:26:02 by sawang            #+#    #+#             */
/*   Updated: 2023/04/25 16:02:44 by sawang           ###   ########.fr       */
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
	UNINITIALIZED,
	INITIALIZED,//?
	NOT_STARTED,
	START
}			t_start_status;

typedef enum e_kill_status
{
	UNINITIALIZED,
	INITIALIZED,//?
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

#endif
// table.dead;
// mutex_lock(&philo->table->dead_signal);
// philo.table.dead_signal = true;
// philo.table.time_to_die
// mutex_unlock(&philo->table->dead_signal);
