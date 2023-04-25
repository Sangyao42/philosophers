/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:57:21 by sawang            #+#    #+#             */
/*   Updated: 2023/04/25 22:57:35 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_eat(struct s_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->mutex_l_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->mutex_r_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->table->traffic_light.mutex_kill);
		philo->eat_cnt++;
		philo->last_eat = time_passed(philo->start_time);
		pthread_mutex_unlock(&philo->table->traffic_light.mutex_kill);
		print_status(philo, "is eating");
		sleep_better(philo->table->input.time_to_eat);
		pthread_mutex_unlock(philo->mutex_r_fork);
		pthread_mutex_unlock(philo->mutex_l_fork);
		philo->status = EATING;
	}
	else
	{
		pthread_mutex_lock(philo->mutex_r_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->mutex_l_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->table->traffic_light.mutex_kill);
		philo->eat_cnt++;
		philo->last_eat = time_passed(philo->start_time);
		pthread_mutex_unlock(&philo->table->traffic_light.mutex_kill);
		print_status(philo, "is eating");
		sleep_better(philo->table->input.time_to_eat);
		pthread_mutex_unlock(philo->mutex_l_fork);
		pthread_mutex_unlock(philo->mutex_r_fork);
		philo->status = EATING;
	}
}

static void	philo_sleep(struct s_philo *philo)
{
	print_status(philo, "is sleeping");
	sleep_better(philo->table->input.time_to_sleep);
	philo->status = SLEEPING;
}

static void	philo_think(struct s_philo *philo)
{
	print_status(philo, "is thinking");
	philo->status = THINKING;
}

void	philo_activity(struct s_philo *philo)
{
	if (philo->status == THINKING)
	{
		philo_eat(philo);
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