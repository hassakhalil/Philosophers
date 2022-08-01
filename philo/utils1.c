/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:38:12 by hkhalil           #+#    #+#             */
/*   Updated: 2022/08/01 19:18:50 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	time_now(t_philo *s)
{
	gettimeofday(&(s->tp), NULL);
	return (1000 * ((s->tp).tv_sec) + ((s->tp).tv_usec) / 1000);
}

int	supervisor(t_philo *s)
{
	if ((time_now(s) - (s->last_meal)) > s->args->time_to_die)
	{
		if (s->args->done == s->args->number_of_philosophers)
			return (1);
		if (s->meals == s->args->number_of_times_each_philosopher_must_eat)
			(s->args->done)++;
		else
		{
			print(s, 4);
			return (-1);
		}
	}
	return (0);
}

void	free_args(t_arguments *s)
{
	free(s->fork);
	free(s);
}

void    fill_args(t_arguments **args, int argc, char *argv[])
{
    int i;

    (*args) = malloc(sizeof(t_arguments));
	(**args).number_of_philosophers = ft_atoi(argv[1]);
	(**args).time_to_die = ft_atoi(argv[2]);
	(**args).time_to_eat = ft_atoi(argv[3]);
	(**args).time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		(**args).number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		(**args).number_of_times_each_philosopher_must_eat = -1;
	(**args).done = 0;
	(**args).fork = malloc(sizeof(pthread_mutex_t)
			* (**args).number_of_philosophers);
    pthread_mutex_init(&((**args).print_logs), NULL);
	pthread_mutex_init(&((**args).eating), NULL);
    i = 0;
	while (i < (**args).number_of_philosophers)
	{
		pthread_mutex_init(&(((**args).fork)[i]), NULL);
		i++;
	}
}
