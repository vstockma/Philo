/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:41:56 by valentin          #+#    #+#             */
/*   Updated: 2023/03/16 14:39:07 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int    init_comb(t_var *vars, char **av)
{
    if (init_input(vars, av) != 0)
    {
        printf("Error!\nWrong values for input!");
        return (1);
    }
    if (init_forks(vars) != 0)
        return (1);
    init_philos(vars);
}

int init_philos(t_var *vars)
{
    int i;

    i = 0;
    while (i < vars->phil_num)
    {
        vars->philos[i].eat_counter = 0;
        vars->philos[i].stat = 0;
        vars->philos[i].time_he_dies = vars->t_die;
        vars->philos[i].id = i + 1;
        pthread_mutex_init(&vars->philos[i].lock, NULL);
        pthread_mutex_init(&vars->printf, NULL);
    }
}

int init_forks(t_var *vars)
{
    int i;

    i = 0;
    while (i < vars->phil_num)
    {
        pthread_mutex_init(&vars->forks[i], NULL);
        i++;
    }
    vars->philos->lf = &vars->forks[0];
    vars->philos->rf = &vars->forks[vars->phil_num - 1];
    i = 1;
    while (i < vars->phil_num)
    {
        vars->philos[i].lf = &vars->forks[i];
        vars->philos[i].rf = &vars->forks[i - 1];
        i++;
    }
    return (0);
}

int    init_input(t_var *vars, char **av)
{
    vars->phil_num = ft_atoi(av[1]);
    vars->t_die = ft_atoi(av[2]);
    vars->t_eat = ft_atoi(av[3]);
    vars->t_sleep = ft_atoi(av[4]);
    if (vars->phil_num < 1 || vars->phil_num > 200 || vars->t_die < 0 ||
        vars->t_eat < 0 || vars->t_sleep < 0)
        return (1);
    if (av[5])
    {
        vars->count_to_eat = ft_atoi(av[5]);
        if (vars->count_to_eat <= 0)
            return (1);
    }
    else
        vars->count_to_eat = -1;
    vars->start_time = current_timestamp();
    vars->dead = 0;
    vars->finish = 0;
    pthread_mutex_init(&vars->lock, NULL);
    return (0);
}