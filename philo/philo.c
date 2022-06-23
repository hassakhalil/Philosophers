/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <hkhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 04:01:55 by hkhalil           #+#    #+#             */
/*   Updated: 2022/06/23 15:35:20 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *args)
{
	t_arguments *s;

	s = (t_arguments *)args;
	while (1)
	{
		pthread_mutex_lock(&((*s).fork[(*s).philosopher_index]));
		printf("%d has taken a fork\n", (*s).philosopher_index);
		pthread_mutex_lock(&((*s).fork[(*s).philosopher_index + 1]));
		printf("%d has taken a fork\n", (*s).philosopher_index);
		printf("%d is eating\n", (*s).philosopher_index);
		usleep(((*s).time_to_eat) * 1000);
		pthread_mutex_unlock(&((*s).fork[(*s).philosopher_index]));
		pthread_mutex_unlock(&((*s).fork[(*s).philosopher_index + 1]));
		//if (philo is still alive)
		//	->eat
		//else
		//{
		//	printf("%d died\n", (*args).philosopher_index);
		//	//free
		//	exit(0);
	//	}
		printf("%d is sleeping\n", (*s).philosopher_index);
		usleep(((*s).time_to_sleep) * 1000);
		printf("%d is thinking\n", (*s).philosopher_index);
	}
}
int	main(int argc, char *argv[])
{
	pthread_t	*th;
	t_arguments args;

	if (check_for_errors(argc, argv) == -1)
		return (-1);
	args.number_of_philosophers = ft_atoi(argv[1]);
	args.time_to_die = ft_atoi(argv[2]);
	args.time_to_eat = ft_atoi(argv[3]);
	args.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	th = malloc(sizeof(pthread_t) * args.number_of_philosophers);
	args.fork = malloc(sizeof(pthread_mutex_t) * args.number_of_philosophers);
	args.philosopher_index= 0;
	while (args.philosopher_index < args.number_of_philosophers)
	{
		if (pthread_create(&th[args.philosopher_index], NULL, &routine, &args))
		{
			return (-1);
		}
		(args.philosopher_index)++;
	}
	return (0);
}
