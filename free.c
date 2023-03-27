/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:36:11 by valentin          #+#    #+#             */
/*   Updated: 2023/03/27 13:43:11 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_free_destroy(t_var *vars)
{
    int i;

    i = 0;
    while (i < vars->phil_num)
    {
        pthread_mutex_destroy(&vars->m_forks[i]);
        i++;
    }
    pthread_mutex_destroy(&vars->printf);
    pthread_mutex_destroy(&vars->lock);
    free(vars->m_forks);
    free(vars->forks);
    free(vars->philos);
    free(vars);
    exit (0);
}