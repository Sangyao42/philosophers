/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:57:21 by sawang            #+#    #+#             */
/*   Updated: 2023/05/10 13:24:34 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_odd_eat(struct s_philo *philo)
{
	pthread_mutex_lock(philo->mutex_l_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->mutex_r_fork);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(philo->mutex_check_eat);
	philo->eat_cnt += 1;
	philo->last_eat = time_now();
	pthread_mutex_unlock(philo->mutex_check_eat);
	sleep_better(philo->table->input.time_to_eat, philo->table);
	pthread_mutex_unlock(philo->mutex_r_fork);
	pthread_mutex_unlock(philo->mutex_l_fork);
	philo->status = EATING;
}

static void	philo_even_eat(struct s_philo *philo)
{
	pthread_mutex_lock(philo->mutex_r_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->mutex_l_fork);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(philo->mutex_check_eat);
	philo->eat_cnt += 1;
	philo->last_eat = time_now();
	pthread_mutex_unlock(philo->mutex_check_eat);
	sleep_better(philo->table->input.time_to_eat, philo->table);
	pthread_mutex_unlock(philo->mutex_l_fork);
	pthread_mutex_unlock(philo->mutex_r_fork);
	philo->status = EATING;
}

static void	philo_sleep(struct s_philo *philo)
{
	print_status(philo, "is sleeping");
	sleep_better(philo->table->input.time_to_sleep, philo->table);
	philo->status = SLEEPING;
}

static void	philo_think(struct s_philo *philo)
{
	t_milliseconds	time_to_think;

	print_status(philo, "is thinking");
	time_to_think = time_passed(philo->last_eat);
	if (philo->table->input.time_to_die > time_to_think)
	{
		time_to_think \
			= (philo->table->input.time_to_die - time_to_think) * 7 / 10;
		sleep_better(time_to_think, philo->table);
	}
	philo->status = THINKING;
}

void	philo_activity(struct s_philo *philo)
{
	if (philo->status == THINKING)
	{
		if (philo->id % 2 == 1)
			philo_odd_eat(philo);
		else
			philo_even_eat(philo);
		return ;
	}
	if (philo->status == EATING)
	{
		philo_sleep(philo);
		return ;
	}
	if (philo->status == SLEEPING)
	{
		philo_think(philo);
		return ;
	}
}
