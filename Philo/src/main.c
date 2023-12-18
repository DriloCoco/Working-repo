/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicsanch <nico_sp_92@hotmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 18:41:20 by nicsanch          #+#    #+#             */
/*   Updated: 2023/09/28 19:11:08 by nicsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	ft_init_rules(t_table *table, int argc, char **argv)
{
	table->rules = malloc(sizeof(t_rules *));
	if (!(table->rules))
	{
		printf("\nFailed on malloc");
	}
	table->rules->n_philos = ft_atoi(argv[1]);
	table->rules->time_to_die = ft_atoi(argv[2]);
	table->rules->time_to_eat = ft_atoi(argv[3]);
	table->rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->rules->n_meals = ft_atoi(argv[5]);
}

void ft_init_forks(t_table *table)
{
	int i;

	i = -1;
	table->forks = malloc(sizeof(pthread_mutex_t **));
	while (++i < table->rules->n_philos)
	{
		table->forks[i] = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init((table->forks[i]), NULL);
	}
	i = 0;
	table->philos[0].l_fork = (table->forks[0]);
	table->philos[0].r_fork = (table->forks[table->rules->n_philos - 1]);
	while(++i < table->rules->n_philos)
	{
		table->philos[i].l_fork = (table->forks[i]);
		table->philos[i].r_fork = (table->forks[i -1]);
	}
}

void	ft_init_philos(t_table *table)
{
	int i;

	i = -1;
	table->philos = malloc(sizeof(t_philo) * table->rules->n_philos);
	if (!(table->philos))
		printf("\nError: failed on malloc");
	while (++i < table->rules->n_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].last_meal = 0;
		table->philos[i].n_meals = table->rules->n_meals;
		table->philos[i].status = 0;
		table->philos[i].monitor = &(table->monitor);
	}
}

void *ft_action(void *param)
{
	t_philo *philo;

	philo = (t_philo *)param;
	while (1)
	{
        pthread_mutex_lock((philo->monitor));
		while (1)
		{
			philo->status++;
			printf("\nEl filósofo %i entra", philo->id);
			// pthread_mutex_unlock((philo->monitor));
			pthread_mutex_lock(philo->l_fork);
			pthread_mutex_lock(philo->r_fork);
			usleep(50000);
			printf("\nEl filósofo %i cogió tenedores", philo->id);
			pthread_mutex_unlock(philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);
			printf("\nEl filósofo %i dejó tenedores", philo->id);
			pthread_mutex_unlock((philo->monitor));
			usleep(50000);
			philo->status--;

		}

	}

}

void ft_init_threads(t_table *table)
{
	int i;

    table->threads = malloc(table->rules->n_philos * sizeof(pthread_t));
	i = -1;
	while (++i < table->rules->n_philos)
	{
		pthread_create(&table->threads[i], NULL, ft_action, &(table->philos[i]));
	}
	i = -1;
	while (++i < table->rules->n_philos)
	{
		if (pthread_join(table->threads[i], NULL) != 0)
        {
            perror("Error joining thread");
            exit(EXIT_FAILURE);
        }
		usleep(1000000);
	}	
}

void ft_init_table(t_table *table, int argc, char **argv)
{
	ft_init_rules(table, argc, argv);
	pthread_mutex_init(&(table->monitor), NULL);
	ft_init_philos(table);
	ft_init_forks(table);
	ft_init_threads(table);
}

void ft_print_table(t_table *table)
{
	printf("\nTable rules:\nNumber of philos = %i", table->rules->n_philos);
	printf("\nTime to die = %i", table->rules->time_to_die);
	printf("\nTime to eat = %i", table->rules->time_to_eat);
	printf("\nTime to sleep = %i", table->rules->time_to_sleep);
	printf("\nNumber of meals = %i", table->rules->n_meals);
}

int	main(int argc, char **argv)
{
	t_table	table;	ft_atoi(argv[1]);

	if (argc != 5 && argc != 6)
	{
		printf("\nError: philo needs 5 or 6 arguments.");
		return (EXIT_FAILURE);
	}
    struct timeval inicio;
	struct timeval tv;
	struct timeval now;


    gettimeofday(&inicio, NULL);
	usleep(200);
    gettimeofday(&now, NULL);
	tv.tv_usec = now.tv_usec - inicio.tv_usec;
    // printf("Seconds: %ld\n", tv.tv_sec);
    printf("Microseconds: %ld\n", tv.tv_usec);
	ft_atoi(argv[1]);
	ft_init_table(&table, argc, argv);
	ft_print_table(&table);
	return (0);
}
