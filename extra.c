/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:49:02 by vstockma          #+#    #+#             */
/*   Updated: 2023/03/17 13:06:10 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_put(t_var *vars, char *s, int id)
{
    long long zeit;

    pthread_mutex_lock(&vars->printf);
    zeit = current_timestamp() - vars->start_time;
    if (ft_strncmp(s, "died", 4) == 0 && vars->dead == 0)
    {
        vars->dead++;
        printf("%lld %i %s", zeit, id, s);
    }
    if (!vars->dead && vars->finish != vars->count_to_eat)
        printf("%lld %i %s", zeit, id, s);
    pthread_mutex_unlock(&vars->printf);
}

void    ft_sleep(int time)
{
    long int s;
    s = current_timestamp();
    while (current_timestamp() - s < time)
        usleep(time / 10);
}