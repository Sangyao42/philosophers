/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_setter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 22:37:27 by sawang            #+#    #+#             */
/*   Updated: 2023/05/09 17:50:05 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_valid_uint(const char *str)
{
	int				i;
	unsigned long	value;

	if (!*str)
		return (EXIT_FAILURE);
	i = 0;
	value = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (EXIT_FAILURE);
		value = value * 10 + (str[i] - '0');
		if (value > UINT_MAX)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static bool	is_valid_ulong(const char *str)
{
	int					i;
	unsigned long long	value;

	if (!*str)
		return (EXIT_FAILURE);
	i = 0;
	value = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (EXIT_FAILURE);
		value = value * 10 + (str[i] - '0');
		if (value > ULONG_MAX)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static bool	check_input(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
		return (EXIT_FAILURE);
	if (is_valid_uint(argv[1]) || \
		is_valid_ulong(argv[2]) || \
		is_valid_ulong(argv[3]) || \
		is_valid_ulong(argv[4]))
		return (EXIT_FAILURE);
	if (argc == 6)
	{
		if (is_valid_uint(argv[5]))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

bool	set_input(struct s_table *table, int argc, char *argv[])
{
	if (check_input(argc, argv) == EXIT_FAILURE)
	{
		printf("Error: Invalid input");
		return (EXIT_FAILURE);
	}
	table->input.num_of_philos = philo_atoi(argv[1]);
	table->input.time_to_die = philo_atoi(argv[2]);
	table->input.time_to_eat = philo_atoi(argv[3]);
	table->input.time_to_sleep = philo_atoi(argv[4]);
	if (argc == 6)
		table->input.num_of_must_eat = philo_atoi(argv[5]);
	else
		table->input.num_of_must_eat = UINT_MAX;
	if (table->input.num_of_philos < 1)
	{
		printf("Error: Number of philosophers must be at least 1");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
