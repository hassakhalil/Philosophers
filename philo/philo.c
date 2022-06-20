/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <hkhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 04:01:55 by hkhalil           #+#    #+#             */
/*   Updated: 2022/06/20 23:15:59 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *args)
{
	(t_arguments *)args;
	while (1)
	{
			printf("%d is thinking\n", (*args).philosopher_index);
			//keep thinking until both forks are free (use mutex!!!!)
			pthread_mutex_lock(&((*args).mutex));
			printf("%d has taken a fork\n", (*args).philosopher_index);
			((*args).forks)[(*args).philosopher_index - 1] = 1;
			pthread_mutex_unlock(&((*args).mutex));
			pthread_mutex_lock(&((*args).mutex));
			printf("%d has taken a fork\n", (*args).philosopher_index);
			((*args).forks)[(*args).philosopher_index] = 1;
			pthread_mutex_unlock(&((*args).mutex));
			if (((*args).forks)[(*args).philosopher_index] == 1 && ((*args).forks)[(*args).philosopher_index - 1] == 1)
			{
				printf("%d is eating\n", (*args).philosopher_index);
				((*args).forks)[(*args).philosopher_index] == 0;
				((*args).forks)[(*args).philosopher_index - 1] == 0;
			}
		if (philo is still alive)
			->eat
		else
		{
			printf("%d died\n", (*args).philosopher_index);
			//free
			exit(0);
		}
		printf("%d is sleeping\n", (*args).philosopher_index);
		usleep(((*args).time_to_sleep) * 1000);
	}
}
int	main(int argc, char *argv[])
{
	pthread_t	*th;
	t_arguments args;
	int			l;

	if (check_for_errors(argc, argv) == -1)
		return (-1);
	args.number_of_philosophers = ft_atoi(argv[1]);
	args.time_to_die = ft_atoi(argv[2]);
	args.time_to_eat = ft_atoi(argv[3]);
	args.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	args.forks = malloc(sizeof(int) * args.number_of_philosophers);
	l = 0;
	while (l < args.number_of_philosophers)
	{
		(args.forks)[l] = 0;
		l++;
	}
	th = malloc(sizeof(pthread_t) * args.number_of_philosophers);
	args.philosopher_index= 1;
	while (args.philosopher_index <= args.number_of_philosophers)
	{
		if (pthread_create(&th[(args.philosopher_index) - 1], NULL, &routine, &args))
		{
			return (-1);
		}
		(args.philosopher_index)++;
	}
	return (0);
}
