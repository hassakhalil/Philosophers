/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <hkhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 01:23:41 by hkhalil           #+#    #+#             */
/*   Updated: 2022/06/24 16:50:32 by hkhalil          ###   ########.fr       */
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

void	print(t_arguments *s, int state,int index)
{
	pthread_mutex_lock(&((*s).print_logs));
	if (state == 0)
		printf("%ld %d has taken a fork\n", (time_now(s) - ((s->philo)[index]).start) * 1000, index + 1);
	else if (state == 1)
	{
		
		printf("%ld %d is eating\n", (time_now(s) - ((s->philo)[index]).start) * 1000, index + 1);
	}
	else if (state == 2)
		printf("%ld %d is sleeping\n", (time_now(s) - ((s->philo)[index]).start) * 1000, index + 1);
	else if (state == 3)
		printf("%ld %d is thinking\n", (time_now(s) - ((s->philo)[index]).start) * 1000, index + 1);
	else
		printf("%ld %d died\n", (time_now(s) - ((s->philo)[index]).start) * 1000, index + 1);
	pthread_mutex_unlock(&((*s).print_logs));
}

long	time_now(t_arguments *s)
{
	gettimeofday((s->philo)->tp, NULL);
	return (((s->philo)->tp)->tv_sec);
}