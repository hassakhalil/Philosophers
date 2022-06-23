/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <hkhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 04:01:55 by hkhalil           #+#    #+#             */
/*   Updated: 2022/06/23 18:32:12 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *args)
{
	t_arguments *s;
	int			n;

	s = (t_arguments *)args;
	if ((*s).philosopher_index + 1 == (*s).number_of_philosophers)
		n = 0;
	else
		n = (*s).philosopher_index;
	while (1)
	{
		pthread_mutex_lock(&(((*s).fork)[(*s).philosopher_index]));
		printf("%d has taken a fork\n", n + 1);
		pthread_mutex_lock(&(((*s).fork)[n + 1]));
		printf("%d has taken a fork\n", n + 1);
		printf("%d is eating\n", n + 1);
		usleep(((*s).time_to_eat) * 1000);
		pthread_mutex_unlock(&(((*s).fork)[(*s).philosopher_index]));
		pthread_mutex_unlock(&(((*s).fork)[n + 1]));
		printf("%d is sleeping\n", n + 1);
		usleep(((*s).time_to_sleep) * 1000);
		printf("%d is thinking\n", n + 1);
	}
}
int	main(int argc, char *argv[])
{
	t_arguments *args;
	int			i = 0;

	if (check_for_errors(argc, argv) == -1)
		return (-1);
	args = malloc(sizeof(t_arguments));
	(*args).number_of_philosophers = ft_atoi(argv[1]);
	(*args).time_to_die = ft_atoi(argv[2]);
	(*args).time_to_eat = ft_atoi(argv[3]);
	(*args).time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		(*args).number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	(*args).th = malloc(sizeof(pthread_t) * (*args).number_of_philosophers);
	(*args).fork = malloc(sizeof(pthread_mutex_t) * (*args).number_of_philosophers);
	while (i < (*args).number_of_philosophers)
	{
		pthread_mutex_init(&(((*args).fork)[i]), NULL);
		i++;
	}
	(*args).philosopher_index = 0;
	while ((*args).philosopher_index < (*args).number_of_philosophers)
	{
		if (pthread_create(&((*args).th)[(*args).philosopher_index], NULL, &routine, args))
		{
			return (-1);
		}
		((*args).philosopher_index)++;
	}
	i = 0;
	while (i < (*args).number_of_philosophers)
	{
		if (pthread_join(((*args).th)[i], NULL))
		{
			return (-1);
		}
		i++;
	}
	while (i < (*args).number_of_philosophers)
	{
		pthread_mutex_destroy(&(((*args).fork)[i]));
		i++;
	}
	return (0);
}
