/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 04:09:46 by hkhalil           #+#    #+#             */
/*   Updated: 2022/08/03 00:08:27 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_arguments
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				done;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print_logs;
	pthread_mutex_t	eating;
	pthread_mutex_t	meal_lock;
}	t_arguments;

typedef struct s_philo
{
	int				index;
	int				left;
	int				right;
	pthread_t		th;
	struct timeval	tp;
	long long		start;
	long long		last_meal;
	int				meals;
	t_arguments		*args;
}	t_philo;

int			check_for_errors(int argc, char *argv[]);
void		fill_args(t_arguments **args, int argc, char *argv[]);
void		fill_philo(t_philo **philo, t_arguments *args);
int			start_philo(t_philo **philo, t_arguments *args,
				void *(*routine)(void *));
int			ft_atoi(const char *nptr);
void		print(t_philo *s, int statemake);
long long	time_now(t_philo *s);
int			supervisor(t_philo*s);
void		free_all(t_arguments *s, t_philo *philo);
void		destroy_mutex(t_arguments *args);
void		supervisor_inside(t_philo *philo, t_arguments *args);
void		clean(t_arguments *args, t_philo *philo);
#endif
