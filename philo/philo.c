/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 04:01:55 by hkhalil           #+#    #+#             */
/*   Updated: 2022/07/31 02:41:47 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *philo)
{
	t_philo *s;
	int i;

	s = (t_philo *)philo;
	i = s->index;
	while (1)
	{
		pthread_mutex_lock(&(((*s).args->fork)[s->left]));
		print(s, 0, i);
		pthread_mutex_lock(&(((*s).args->fork)[s->right]));
		print(s, 0, i);
		print(s, 1, i);
		usleep(((s->args)->time_to_eat) * 1000);
		pthread_mutex_unlock(&(((*s).args->fork)[s->left]));
		pthread_mutex_unlock(&(((*s).args->fork)[s->right]));
		print(s, 2, i);
		usleep((s->args->time_to_sleep) * 1000);
		print(s, 3, i);
	}
}
int main(int argc, char *argv[])
{
	t_arguments *args;
	t_philo *philo;
	int i;
	long long time;

	if (check_for_errors(argc, argv) == -1)
		return (-1);
	args = malloc(sizeof(t_arguments));
	(*args).number_of_philosophers = ft_atoi(argv[1]);
	(*args).time_to_die = ft_atoi(argv[2]);
	(*args).time_to_eat = ft_atoi(argv[3]);
	(*args).time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		(*args).number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		(*args).number_of_times_each_philosopher_must_eat  = -1;
	philo = malloc(sizeof(t_philo) * ((*args).number_of_philosophers));
	(*args).fork = malloc(sizeof(pthread_mutex_t) * (*args).number_of_philosophers);
	i = 0;
	while (i < (*args).number_of_philosophers)
	{
		philo[i].args = args;
		i++;
	}
	pthread_mutex_init(&((*args).print_logs), NULL);
	i = 0;
	while (i < (*args).number_of_philosophers)
	{
		pthread_mutex_init(&(((*args).fork)[i]), NULL);
		i++;
	}
	i = 0;
	time = time_now(&philo[i]);
	while (i < (*args).number_of_philosophers)
	{
		(philo[i]).index = i;
		(philo[i]).meals = 0;
		if (i == args->number_of_philosophers - 1)
			(philo[i]).right = 0;
		else
			(philo[i]).right = i + 1;
		(philo[i]).left = i;
		(philo[i]).start = time;
		(philo[i]).last_meal = time;
		if (pthread_create(&(philo[i].th), NULL, &routine, &philo[i]))
		{
			return (-1);
		}
		i++;
	}
	while (1)
	{
		i = 0;
		while (i < args->number_of_philosophers)
		{
			supervisor(&philo[i]);
			i++;
		}
		usleep(5000);
	}
	i = 0;
	while (i < (*args).number_of_philosophers)
	{
		if (pthread_join((philo[i]).th, NULL))
		{
			return (-1);
		}
		i++;
	}
	i = 0;
	while (i < (*args).number_of_philosophers)
	{
		pthread_mutex_destroy(&(((*args).fork)[i]));
		i++;
	}
	pthread_mutex_destroy(&((*args).print_logs));
	return (0);
}
