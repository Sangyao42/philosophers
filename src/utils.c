/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 21:21:11 by sawang            #+#    #+#             */
/*   Updated: 2023/05/07 20:10:39 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdint.h>

int	philo_strcmp(char *s1, char *s2)
{
	int	i;
	int	ret_val;

	i = 0;
	ret_val = 0;
	while (s1[i] || s2[i])
	{
		ret_val = s1[i] - s2[i];
		if (ret_val != 0)
			return (ret_val);
		else
			ret_val = 0;
		i++;
	}
	return (ret_val);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*mem;
	size_t	i;

	if (size && count > SIZE_MAX / size)
		return (NULL);
	mem = malloc(count * size);
	if (mem)
	{
		i = 0;
		while (i < (count * size))
		{
			mem[i] = 0;
			i++;
		}
		return (mem);
	}
	return (NULL);
}

unsigned long	philo_atoi(const char *str)
{
	int				i;
	unsigned long	value;

	i = 0;
	value = 0;
	while (str[i])
	{
		value = value * 10 + (str[i] - '0');
		i++;
	}
	return (value);
}
