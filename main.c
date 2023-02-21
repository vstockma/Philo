/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:21:52 by valentin          #+#    #+#             */
/*   Updated: 2023/02/21 12:07:28 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    init_input5(t_var *vars, char **av)
{
    vars->phil_num = ft_atoi(av[1]);
    vars->t_die = ft_atoi(av[2]);
    vars->t_eat = ft_atoi(av[3]);
    vars->t_sleep = ft_atoi(av[4]);
}

void    init_input6(t_var *vars, char **av)
{
    vars->phil_num = ft_atoi(av[1]);
    vars->t_die = ft_atoi(av[2]);
    vars->t_eat = ft_atoi(av[3]);
    vars->t_sleep = ft_atoi(av[4]);
    vars->count_to_eat = ft_atoi(av[5]);
}

int main(int ac, char **av)
{
    t_var *vars;

    vars = (t_var *)malloc(sizeof(t_var));
    if (ac == 5 || ac == 6)
        ft_error_check(vars, av);
    if (ac == 5)
    {
        init_input5(vars, av);
        ft_arg5(vars);
    }
    else if (ac == 6)
    {
        init_input6(vars, av);
        ft_arg6(vars);
    }
    else
        ft_free(vars);
    ft_free(vars);
    return (0);
}