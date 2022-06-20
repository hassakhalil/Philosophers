/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <hkhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 04:01:55 by hkhalil           #+#    #+#             */
/*   Updated: 2022/06/20 21:38:04 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *args)
{
	(t_arguments *)args;
	/*while (philo alive)
{
	keep thinking until both forks are free (use mutex!!!!)
	if (philo is still alive)
		->eat
	else
		->stop
	sleep
}*/
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
