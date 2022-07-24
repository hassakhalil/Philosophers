/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <hkhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 04:09:46 by hkhalil           #+#    #+#             */
/*   Updated: 2022/06/25 00:08:09 by hkhalil          ###   ########.fr       */
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
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
    int index;
    pthread_mutex_t *fork;
    pthread_mutex_t print_logs;
}   t_arguments;

typedef struct s_philo
{
    int             index;
    pthread_t	    th;
    struct timeval tp;
    long long       start;
    long long       last_meal;
    long long       time_of_death;
    t_arguments     *args;
}   t_philo;


int     check_for_errors(int argc, char *argv[]);
int     ft_atoi(const char *nptr);
void    print(t_philo *s, int state, int index);
long long	time_now(t_philo *s);
void	supervisor(t_philo*s);
#endif
