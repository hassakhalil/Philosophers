/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 00:19:23 by hkhalil           #+#    #+#             */
/*   Updated: 2022/08/02 23:41:02 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_philo(t_philo **philo, t_arguments *args, void *(*routine)(void *))
{
	int			i;
	long long	time;

	i = 0;
	time = time_now(&(*philo)[i]);
	while (i < args->number_of_philosophers)
	{
		((*philo)[i]).start = time;
		((*philo)[i]).last_meal = time;
		if (pthread_create(&((*philo)[i].th), NULL, routine, &(*philo)[i]))
			return (-1);
		usleep(1000);
		i++;
	}
	return (0);
}

void	destroy_mutex(t_arguments *args)
{
	int	i;

	i = 0;
	while (i < (*args).number_of_philosophers)
	{
		pthread_mutex_destroy(&(((*args).fork)[i]));
		i++;
	}
	pthread_mutex_destroy(&((*args).print_logs));
	pthread_mutex_destroy(&((*args).eating));
}

void	supervisor_inside(t_philo *philo, t_arguments *args)
{
	int	flag;
	int	i;

	while (1)
	{
		i = 0;
		flag = 0;
		while (i < args->number_of_philosophers)
		{
			if (supervisor(&(philo)[i]))
			{
				flag = 1;
				break ;
			}
			i++;
		}
		if (flag == 1)
			break ;
		usleep(1000);
	}
}

void	clean(t_arguments *args, t_philo *philo)
{
	destroy_mutex(args);
	free_all(args, philo);
}
