/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:38:12 by hkhalil           #+#    #+#             */
/*   Updated: 2022/08/03 00:04:21 by hkhalil          ###   ########.fr       */
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
	pthread_mutex_lock(&(s->args->superv));
	if ((time_now(s) - (s->last_meal)) > s->args->time_to_die)
	{
		pthread_mutex_unlock(&(s->args->superv));
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
	pthread_mutex_unlock(&(s->args->superv));
	return (0);
}

void	free_all(t_arguments *s, t_philo *philo)
{
	free(s->fork);
	free(s);
	free(philo);
}

void	fill_args(t_arguments **args, int argc, char *argv[])
{
	int	i;

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
	pthread_mutex_init(&((**args).superv), NULL);
	i = 0;
	while (i < (**args).number_of_philosophers)
	{
		pthread_mutex_init(&(((**args).fork)[i]), NULL);
		i++;
	}
}

void	fill_philo(t_philo **philo, t_arguments *args)
{
	int	i;

	(*philo) = malloc(sizeof(t_philo) * ((*args).number_of_philosophers));
	i = 0;
	while (i < (*args).number_of_philosophers)
	{
		(*philo)[i].args = args;
		((*philo)[i]).index = i;
		((*philo)[i]).meals = 0;
		if (i == args->number_of_philosophers - 1)
			((*philo)[i]).right = 0;
		else
			((*philo)[i]).right = i + 1;
		((*philo)[i]).left = i;
		i++;
	}
}
