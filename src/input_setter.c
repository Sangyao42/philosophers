/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_setter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 22:37:27 by sawang            #+#    #+#             */
/*   Updated: 2023/04/24 13:58:04 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_valid_uint(const char *str)
{
	int				i;
	unsigned long	value;

	if (!*str)
		return (EXIT_FAILURE);
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

bool	is_valid_ulong(const char *str)
{
	int					i;
	unsigned long long	value;

	if (!*str)
		return (EXIT_FAILURE);
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

bool	check_input(int argc, char *argv[])
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
		return (ft_printf("Error: Invalid input:"), EXIT_FAILURE);
	if (ft_atoi(argv[1]) < 1)
		return (ft_printf("Error: Number of philosophers must be at least 1"),
			EXIT_FAILURE);
	table->input.num_of_philos = ft_atoi(argv[1]);
	table->input.time_to_die = ft_atoi(argv[2]);
	table->input.time_to_eat = ft_atoi(argv[3]);
	table->input.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->input.num_of_must_eat = ft_atoi(argv[5]);
	else
		table->input.num_of_must_eat = -1;
	return (EXIT_SUCCESS);
}
