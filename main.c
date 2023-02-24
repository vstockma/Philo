/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:21:52 by valentin          #+#    #+#             */
/*   Updated: 2023/02/24 13:20:35 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int    init_input(t_var *vars, char **av)
{
    vars->phil_num = ft_atoi(av[1]);
    vars->t_die = ft_atoi(av[2]);
    vars->t_eat = ft_atoi(av[3]);
    vars->t_sleep = ft_atoi(av[4]);
    if (vars->phil_num <= 1 || vars->t_die < 0 || vars->t_eat < 0 ||
        vars->t_sleep < 0)
        return (1);
    if (av[5])
    {
        vars->count_to_eat = ft_atoi(av[5]);
        if (vars->count_to_eat <= 0)
            return (1);
    }
    else
        vars->count_to_eat = 0;
    return (0);
}

int main(int ac, char **av)
{
    t_var *vars;

    vars = (t_var *)malloc(sizeof(t_var));
    if (ac != 5 || ac != 6)
    {
        printf("Error!\nWrong amount of arguments!");
        ft_free(vars); 
    }
    ft_error_check(vars, av);
    if (init_input(vars, av) != 0)
    {
        printf("Error!\nWrong values for input!");
        free(vars);
    }
    ft_free(vars);
    return (0);
}