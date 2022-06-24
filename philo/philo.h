/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <hkhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 04:09:46 by hkhalil           #+#    #+#             */
/*   Updated: 2022/06/24 21:58:26 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
    pthread_t	th;
    struct timeval *restrict tp;
    long    start;
    long    last_meal;
    long    time_of_death;
}   t_philo;

typedef struct s_arguments
{
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
    int index;
    t_philo *philo;
    pthread_mutex_t *fork;
    pthread_mutex_t print_logs;
}   t_arguments;

int     check_for_errors(int argc, char *argv[]);
int     ft_atoi(const char *nptr);
void    print(t_arguments *s, int state, int index);
long	time_now(t_arguments *s, int index);
void	supervisor(t_arguments *s);
#endif
