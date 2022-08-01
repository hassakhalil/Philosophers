/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:38:12 by hkhalil           #+#    #+#             */
/*   Updated: 2022/08/01 18:40:04 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	time_now(t_philo *s)
{
	gettimeofday(&(s->tp), NULL);
	return (1000 * ((s->tp).tv_sec) + ((s->tp).tv_usec) / 1000);
}

int	supervisor(t_philo *s)
{
	if ((time_now(s) - (s->last_meal)) > s->args->time_to_die)
	{
		if (s->args->done == s->args->number_of_philosophers)
			return (1);
		if (s->meals == s->args->number_of_times_each_philosopher_must_eat)
			(s->args->done)++;
		else
		{
			print(s, 4);
			return (-1);
		}
	}
	return (0);
}

void	free_args(t_arguments *s)
{
	free(s->fork);
	free(s);
}
