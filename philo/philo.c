/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 04:01:55 by hkhalil           #+#    #+#             */
/*   Updated: 2022/08/03 00:20:33 by hkhalil          ###   ########.fr       */
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

	if (check_for_errors(argc, argv) == -1)
		return (-1);
	fill_args(&args, argc, argv);
	fill_philo(&philo, args);
	if (start_philo(&philo, args, &routine))
	{
		clean(args, philo);
		return (-1);
	}
	supervisor_inside(philo, args);
	clean(args, philo);
	return (0);
}
