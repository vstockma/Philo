/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:39:37 by vstockma          #+#    #+#             */
/*   Updated: 2023/03/23 15:12:51 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void routine()
{

}

int ft_1_philo(t_var *vars)
{
    ft_put(vars, "has taken a fork\n", 1);
    ft_sleep(vars->t_die);
    ft_put(vars, "died", 1);
    pthread_mux_destroy(&vars->lock);
    exit(0);
}

int ft_thread_init(t_var *vars)
{
    int i;
    i = -1;
    vars->start_time = current_timestamp();
    while (i++ < vars->phil_num)
    {
        if (pthread_create(&vars->tid[i], NULL, &routine, &vars->philos[i]))
            return (1);
        ft_sleep(1);
    }
    return (0);
    
}