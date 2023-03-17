/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:39:37 by vstockma          #+#    #+#             */
/*   Updated: 2023/03/17 13:04:15 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_1_philo(t_var *vars)
{
    ft_put(vars, "has taken a fork\n", 1);
    ft_sleep(vars->t_die);
    ft_put(vars, "died", 1);
    pthread_mux_destroy(&vars->lock);
    exit(0);
}