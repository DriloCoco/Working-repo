/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicsanch <nico_sp_92@hotmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 20:29:00 by nicsanch          #+#    #+#             */
/*   Updated: 2023/09/26 17:32:10 by nicsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <limits.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>


typedef struct s_philo
{
    pthread_t       philo_thread;
    int id;
    int last_meal;
    pthread_mutex_t*    r_fork;
    pthread_mutex_t*    l_fork;
    pthread_mutex_t*    monitor;
    int n_meals;
    int    status;
}   t_philo;

typedef struct s_rules
{
    int n_philos;
    int time_to_eat;
    int time_to_die;
    int time_to_sleep;
    int n_meals;
}   t_rules;

typedef struct s_table
{
    t_rules*            rules;
    pthread_t*          threads;
    t_philo*           philos;
    pthread_mutex_t**    forks;
	pthread_mutex_t     monitor;
	pthread_mutex_t     write;
    struct timeval start_time;
    int status;
}	t_table;


void ft_print_table(t_table *table);
int	ft_atoi(const char *nptr);


#endif
