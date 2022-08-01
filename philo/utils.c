/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 01:23:41 by hkhalil           #+#    #+#             */
/*   Updated: 2022/08/01 19:01:02 by hkhalil          ###   ########.fr       */
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

void	print_h(t_philo *s, int state, char *msg)
{
	pthread_mutex_lock(&((s->args)->print_logs));
	printf("%lld %d %s\n", time_now(s) - s->start, s->index + 1, msg);
	if (state != 4)
		pthread_mutex_unlock(&((s->args)->print_logs));
}

void	print(t_philo *s, int state)
{
	if (state == 0)
		print_h(s, state, "has taken a fork");
	else if (state == 1)
	{
		s->meals++;
		s->last_meal = time_now(s);
		pthread_mutex_lock(&((s->args)->eating));
		print_h(s, state, "is eating");
		pthread_mutex_unlock(&((s->args)->eating));
	}
	else if (state == 2)
		print_h(s, state, "is sleeping");
	else if (state == 3)
		print_h(s, state, "is thinking");
	else
	{
		pthread_mutex_lock(&((s->args)->eating));
		print_h(s, state, "died");
	}
}
