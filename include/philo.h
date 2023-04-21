/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:26:02 by sawang            #+#    #+#             */
/*   Updated: 2023/04/21 19:24:24 by sawang           ###   ########.fr       */
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

typedef enum e_status
{
	THINKING,
	EATING,
	SLEEPING,
	FORKING,
	DEAD
}				t_status;

typedef struct s_philo
{
	/* data */
	unsigned int	id;
	pthread_mutex_t	*mutex_l_fork;
	pthread_mutex_t	*mutex_r_fork;
	unsigned long	last_eat;
	unsigned int	eat_count;
	struct s_table	*table;
	// t_input			input;

}				t_philo;

typedef struct s_table
{
	/* data */
	// t_input			input;
	unsigned int	num_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	num_of_must_eat;
	t_philo			*philos;
	pthread_mutex_t	*mutex_forks;
	unsigned long	start_time;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_dead;
	bool			dead;
	// pthread_mutex_t	eat_count;
}				t_table;


#endif
table.dead;
mutex_lock(&philo->table->dead_signal);
philo.table.dead_signal = true;
philo.table.time_to_die
mutex_unlock(&philo->table->dead_signal);
