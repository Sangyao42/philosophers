/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 19:08:03 by sawang            #+#    #+#             */
/*   Updated: 2023/04/21 19:23:42 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_valid_uint(const char *str)
{
	int		i;
	long	value;

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

int	check_input(int argc, char *argv[])
{
	int	i;

	if (argc < 5 || argc > 6)
		return (EXIT_FAILURE);
	i = 0;
	while (++i < argc)
	{
		if (is_valid_uint(argv[i]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
