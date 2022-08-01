/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 04:01:55 by hkhalil           #+#    #+#             */
/*   Updated: 2022/08/01 20:10:23 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo)
{
	t_philo	*s;

	s = (t_philo *)philo;
	while (1)
	{
		if (s->meals == s->args->number_of_times_each_philosopher_must_eat)
			return (0);
		pthread_mutex_lock(&(((*s).args->fork)[s->left]));
		print(s, 0);
		pthread_mutex_lock(&(((*s).args->fork)[s->right]));
		print(s, 0);
		print(s, 1);
		usleep(((s->args)->time_to_eat) * 1000);
		pthread_mutex_unlock(&(((*s).args->fork)[s->left]));
		pthread_mutex_unlock(&(((*s).args->fork)[s->right]));
		print(s, 2);
		usleep((s->args->time_to_sleep) * 1000);
		print(s, 3);
	}
}

int	main(int argc, char *argv[])
{
	t_arguments	*args;
	t_philo		*philo;
	int			i;
	int			flag;

	if (check_for_errors(argc, argv) == -1)
		return (-1);
	fill_args(&args, argc, argv);
	fill_philo(&philo, args);
	if (start_philo(&philo, args, &routine))
	{
		//destroy mutexes
		return(-1);
	}
	while (1)
	{
		i = 0;
		flag = 0;
		while (i < args->number_of_philosophers)
		{
			if (supervisor(&philo[i]))
			{
				flag = 1;
				break ;
			}
			i++;
		}
		if (flag == 1)
			break ;
		usleep(5000);
	}
	i = 0;
	while (i < (*args).number_of_philosophers)
	{
		pthread_mutex_destroy(&(((*args).fork)[i]));
		i++;
	}
	pthread_mutex_destroy(&((*args).print_logs));
	pthread_mutex_destroy(&((*args).eating));
	free(philo);
	free_args(args);
	return (0);
}
