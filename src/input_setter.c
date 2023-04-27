/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_setter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 22:37:27 by sawang            #+#    #+#             */
/*   Updated: 2023/04/27 16:43:55 by sawang           ###   ########.fr       */
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
	int	i;

	if (argc < 5 || argc > 6)
		return (EXIT_FAILURE);
	i = 1;
	if (is_valid_uint(argv[i]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (++i < argc && argc == 5)
	{
		if (is_valid_ulong(argv[i]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (argc == 6)
	{
		if (is_valid_uint(argv[i]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

bool	set_input(struct s_table *table, int argc, char *argv[])
{
	if (check_input(argc, argv) == EXIT_FAILURE)
		return (printf("Error: Invalid input:"), EXIT_FAILURE);
	if (philo_atoi(argv[1]) < 1)
		return (printf("Error: Number of philosophers must be at least 1"),
			EXIT_FAILURE);
	table->input.num_of_philos = philo_atoi(argv[1]);
	table->input.time_to_die = philo_atoi(argv[2]);
	table->input.time_to_eat = philo_atoi(argv[3]);
	table->input.time_to_sleep = philo_atoi(argv[4]);
	if (argc == 6)
		table->input.num_of_must_eat = philo_atoi(argv[5]);
	else
		table->input.num_of_must_eat = UINT_MAX;
	// printf("table->input.num_of_philos = %d\n", table->input.num_of_philos);
	// printf("table->input.time_to_die = %lu\n", table->input.time_to_die);
	// printf("table->input.time_to_eat = %lu\n", table->input.time_to_eat);
	// printf("table->input.time_to_sleep = %lu\n", table->input.time_to_sleep);
	// printf("table->input.num_of_must_eat = %u\n", table->input.num_of_must_eat);
	return (EXIT_SUCCESS);
}
