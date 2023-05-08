/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:42:42 by sawang            #+#    #+#             */
/*   Updated: 2023/05/08 15:56:41 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	print_status(struct s_philo *philo, char *doing)
// {
// 	if (philo->table->input.time_to_die == 0 \
// 		|| philo->table->input.num_of_must_eat == 0)
// 		return ;
// 	pthread_mutex_lock(&philo->table->traffic_light.mutex_kill);
// 	if (philo->table->traffic_light.kill == KILL)
// 	{
// 		pthread_mutex_unlock(&philo->table->traffic_light.mutex_kill);
// 		return ;
// 	}
// 	pthread_mutex_unlock(&philo->table->traffic_light.mutex_kill);
// 	pthread_mutex_lock(&philo->table->mutex_print);
// 	if (philo_strcmp(doing, "all philos ate enough") == 0)
// 		printf("%lu %s\n", time_passed(philo->start_time), doing);
// 	else
// 		printf("%lu %d %s\n", time_passed(philo->start_time), \
// 			philo->id, doing);
// 	pthread_mutex_unlock(&philo->table->mutex_print);
// }

void	print_status(struct s_philo *philo, char *doing)
{
	if (philo->table->input.time_to_die == 0 \
		|| philo->table->input.num_of_must_eat == 0)
		return ;
	pthread_mutex_lock(&philo->table->mutex_print);
	pthread_mutex_lock(&philo->table->traffic_light.mutex_kill);
	if (philo->table->traffic_light.kill == KILL)
	{
		pthread_mutex_unlock(&philo->table->traffic_light.mutex_kill);
		if (philo_strcmp(doing, "all philos ate enough") == 0)
			printf("%lu %s\n", time_passed(philo->table->start_time), doing);
		else if (philo_strcmp(doing, "died") == 0)
			printf("%lu %d %s\n", time_passed(philo->table->start_time), \
				philo->id, doing);
		pthread_mutex_unlock(&philo->table->mutex_print);
		return ;
	}
	pthread_mutex_unlock(&philo->table->traffic_light.mutex_kill);
	if (philo_strcmp(doing, "all philos ate enough") == 0)
		printf("%lu %s\n", time_passed(philo->table->start_time), doing);
	else
		printf("%lu %d %s\n", time_passed(philo->table->start_time), \
			philo->id, doing);
	pthread_mutex_unlock(&philo->table->mutex_print);
}

// void	print_status(struct s_philo *philo, char *doing)
// {
// 	if (philo->table->input.time_to_die == 0 \
// 		|| philo->table->input.num_of_must_eat == 0)
// 		return ;
// 	pthread_mutex_lock(&philo->table->traffic_light.mutex_kill);
// 	if (philo->table->traffic_light.kill != KILL)
// 	{
// 		pthread_mutex_lock(&philo->table->mutex_print);
// 		if (philo_strcmp(doing, "all philos ate enough") == 0)
// 			printf("%lu %s\n", time_passed(philo->start_time), doing);
// 		else
// 			printf("%lu %d %s\n", time_passed(philo->start_time), \
// 				philo->id, doing);
// 		pthread_mutex_unlock(&philo->table->mutex_print);
// 	}
// 	pthread_mutex_unlock(&philo->table->traffic_light.mutex_kill);
// 	return ;
// }
