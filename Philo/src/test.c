/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicsanch <nico_sp_92@hotmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:18:28 by nicsanch          #+#    #+#             */
/*   Updated: 2023/09/25 18:17:12 by nicsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_print_table(t_table *table)
{
	printf("\nTable rules:\nNumber of philos = %i", table->rules->n_philos);
	printf("\nTime to die = %i", table->rules->time_to_die);
	printf("\nTime to eat = %i", table->rules->time_to_eat);
	printf("\nTime to sleep = %i", table->rules->time_to_sleep);
	printf("\nNumber of meals = %i", table->rules->n_meals);
}

int	ft_atoi(const char *nptr)
{
	int				counter;
	int				sign;
	int	value;

	value = 0;
	sign = 1;
	counter = 0;
	while (nptr[counter] == 32 || (nptr[counter] > 8 && nptr[counter] < 14))
		counter++;
	if (nptr[counter] == '+' || nptr[counter] == '-')
		if (nptr[counter++] == '-')
			sign = -1 * sign;
	while ((nptr[counter] > 47 && nptr[counter] < 58))
		value = (value * 10) + ((long int) nptr[counter++] - '0');
	if ((nptr[counter] != ' ' && nptr[counter] != '\0')
		|| (value > INT_MAX || value < INT_MIN)
		|| (value == 0 && nptr[counter - 1] != '0'))
	{
		printf("Error\n");
		exit (1);
	}
	return (value * sign);
}