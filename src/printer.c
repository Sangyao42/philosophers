/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:42:42 by sawang            #+#    #+#             */
/*   Updated: 2023/04/25 22:41:23 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(struct s_philo *philo, char *doing)
{
	pthread_mutex_lock(&philo->table->mutex_print);
	printf("%lu %d %s\n", time_passed(philo->start_time), \
		philo->id, doing);
	pthread_mutex_unlock(&philo->table->mutex_print);
}
