/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:36:11 by valentin          #+#    #+#             */
/*   Updated: 2023/03/16 15:01:29 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_free(t_var *vars)
{
    int i;

    i = 0;
    while (i < vars->phil_num)
    {
        pthread_mutex_destroy(&vars->forks[i]);
        pthread_mutex_destroy(&vars->philos[i].lock);
        i++;
    }
    pthread_mutex_destroy(&vars->printf);
    pthread_mutex_destroy(&vars->lock);
    free(vars);
    exit (0);
}