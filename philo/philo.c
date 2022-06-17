/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <hkhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 04:01:55 by hkhalil           #+#    #+#             */
/*   Updated: 2022/06/17 01:51:52 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *args)
{
	(t_arguments *)args;
	
}
int	main(int argc, char *argv[])
{
	pthread_t	*th;
	int			i;
	t_arguments args;

	args.number_of_philosophers = ft_atoi(argv[1]);
	args.time_to_die = ft_atoi(argv[2]);
	args.time_to_eat = ft_atoi(argv[3]);
	args.time_to_sleep = ft_atoi(argv[4]);
	args.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	th = malloc(sizeof(pthread_t) * args.number_of_philosophers);
	i = 0;
	while (i < args.number_of_philosophers)
	{
		th[i] = pthread_create(&th[i], NULL, &routine, &args);
		i++;
	}
	return (0);
}
