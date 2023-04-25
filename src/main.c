/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 21:01:58 by sawang            #+#    #+#             */
/*   Updated: 2023/04/25 22:55:00 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	struct s_table	table;

	if (set_table(&table, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (table.input.num_of_philos == 1)
	{
		if (lonely_philo_simulator(&table) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (philo_dining_simulation(&table) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
