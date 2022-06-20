/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <hkhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 04:01:55 by hkhalil           #+#    #+#             */
/*   Updated: 2022/06/20 16:47:39 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *args)
{
	//(t_arguments *)args;
	return ((void *)args);
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
	args.i = 0;
	while (args.i < args.number_of_philosophers)
	{
		if (pthread_create(&th[args.i], NULL, &routine, &args))
		{
			return (-1);
		}
		(args.i)++;
	}
	return (0);
}
