/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 01:23:41 by hkhalil           #+#    #+#             */
/*   Updated: 2022/07/31 02:18:58 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isspace(int c)
{
	if (c == '\f' || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v' || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int					sign;
	int					i;
	unsigned long long	n;	

	sign = 1;
	i = -1;
	n = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (ft_isdigit(nptr[++i]))
		n = (n * 10) + (nptr[i] - '0');
	if (n > 9223372036854775807)
	{
		if (sign == -1)
			return (0);
		else
			return (-1);
	}
	return (n * sign);
}

void	print(t_philo *s, int state, int i)
{
	if (state == 0)
	{
		pthread_mutex_lock(&((s->args)->print_logs));
		printf("%lld %d has taken a fork\n", time_now(s) - s->start, i + 1);
	}
	else if (state == 1)
	{
		pthread_mutex_lock(&((s->args)->print_logs));
		s->last_meal = time_now(s);
		printf("%lld %d is eating\n", time_now(s) - s->start , i + 1);
	}
	else if (state == 2)
	{
		pthread_mutex_lock(&((s->args)->print_logs));
		printf("%lld %d is sleeping\n", time_now(s) - s->start, i + 1);
	}
	else if (state == 3)
	{
		pthread_mutex_lock(&((s->args)->print_logs));
		printf("%lld %d is thinking\n", time_now(s) - s->start, i + 1);
	}
	else
	{
		pthread_mutex_lock(&((s->args)->print_logs));
		printf("%lld %d died\n", time_now(s) - s->start, i + 1);
	}
	if (state != 4)
		pthread_mutex_unlock(&((s->args)->print_logs));
}

long long	time_now(t_philo *s)
{
	gettimeofday(&(s->tp), NULL);
	return (1000 * ((s->tp).tv_sec) +  ((s->tp).tv_usec) / 1000);
}

void	supervisor(t_philo *s)
{
	if ((time_now(s) - (s->last_meal)) >  s->args->time_to_die)
	{
		print(s, 4, s->index);
		exit(0);
	}
}