/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:24:53 by sawang            #+#    #+#             */
/*   Updated: 2023/05/09 21:22:10 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_milliseconds	time_now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((t_milliseconds)time.tv_sec * 1000 + \
		(t_milliseconds)time.tv_usec / 1000);
}

t_milliseconds	time_passed(t_milliseconds start_time)
{
	return (time_now() - start_time);
}

void	sleep_better(t_milliseconds should_sleep, struct s_table *table)
{
	t_milliseconds	start_time;

	start_time = time_now();
	while (time_passed(start_time) <= should_sleep)
	{
		pthread_mutex_lock(&table->traffic_light.mutex_kill);
		if (table->traffic_light.kill == KILL)
		{
			pthread_mutex_unlock(&table->traffic_light.mutex_kill);
			return ;
		}
		pthread_mutex_unlock(&table->traffic_light.mutex_kill);
		usleep(100);
	}
}
