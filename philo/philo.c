/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <hkhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 04:01:55 by hkhalil           #+#    #+#             */
/*   Updated: 2022/06/24 16:49:08 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *args)
{
	t_arguments *s;
	int			n;
	int			i;

	s = (t_arguments *)args;
	//pthread_mutex_lock(&(s->lock_index));
	i = s->index;
	((s->philo)[s->index]).start = time_now(s);
	//pthread_mutex_unlock(&(s->lock_index));
	if (i + 1 == (*s).number_of_philosophers)
		n = 0;
	else
		n = i + 1;
	//pthread_mutex_unlock(&(s->lock_index));
	while (1)
	{
		pthread_mutex_lock(&(((*s).fork)[i]));
		print(s, 0, i);
		pthread_mutex_lock(&(((*s).fork)[n]));
		print(s, 0, i);
		print(s, 1, i);
		usleep(((*s).time_to_eat) / 1000);
		pthread_mutex_unlock(&(((*s).fork)[i]));
		pthread_mutex_unlock(&(((*s).fork)[n]));
		print(s, 2, i);
		usleep(((*s).time_to_sleep) / 1000);
		print(s, 3, i);
	}
}
int	main(int argc, char *argv[])
{
	t_arguments *args;
	int			i;

	if (check_for_errors(argc, argv) == -1)
		return (-1);
	args = malloc(sizeof(t_arguments));
	(*args).number_of_philosophers = ft_atoi(argv[1]);
	(*args).time_to_die = ft_atoi(argv[2]);
	(*args).time_to_eat = ft_atoi(argv[3]);
	(*args).time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		(*args).number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	(*args).philo = malloc(sizeof(t_philo) * ((*args).number_of_philosophers));
	i = 0;
	while (i < (*args).number_of_philosophers)
	{
		((args->philo)[i]).tp = malloc(sizeof(((args->philo)[i]).tp));
		i++;
	}
	(*args).fork = malloc(sizeof(pthread_mutex_t) * (*args).number_of_philosophers);
	pthread_mutex_init(&((*args).print_logs), NULL);
	pthread_mutex_init(&((*args).lock_index), NULL);
	i = 0;
	while (i < (*args).number_of_philosophers)
	{
		pthread_mutex_init(&(((*args).fork)[i]), NULL);
		i++;
	}
	i = 0;
	while (i < (*args).number_of_philosophers)
	{
		((args->philo)[i]).philosopher_index = i;
		(*args).index = i;
		if (pthread_create(&((args->philo)[i].th), NULL, &routine, args))
		{
			return (-1);
		}
		i++;
	}
	i = 0;
	while (i < (*args).number_of_philosophers)
	{
		if (pthread_join((args->philo)[i].th, NULL))
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
	pthread_mutex_destroy(&((*args).lock_index));
	return (0);
}
