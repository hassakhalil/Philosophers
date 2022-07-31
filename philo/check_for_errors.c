/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:20:11 by hkhalil           #+#    #+#             */
/*   Updated: 2022/07/31 01:37:01 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_number(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (s[i] > '9' || s[i] < '0')
            return (-1);
        i++;
    }
    return (0);
}

int check_for_errors(int argc, char *argv[])
{
    if (argc != 5 && argc != 6)
    {
        printf("Error\n");
        return (-1);
    }
    if (is_number(argv[1]) || is_number(argv[2]) || is_number(argv[3]) || is_number(argv[4]))
    {
        printf("Error\n");
        return(-1);
    }
    if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0)
    {
        printf("Error\n");
        return(-1);
    }
    if (argc == 6)
    {
        if (is_number(argv[5]) || ft_atoi(argv[5]) < 0)
        {
            printf("Error\n");
            return (-1);
        }
    }
    return (0);
}