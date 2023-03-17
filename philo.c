/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:21:52 by valentin          #+#    #+#             */
/*   Updated: 2023/03/16 13:28:50 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    t_var *vars;

    vars = (t_var *)malloc(sizeof(t_var));
    if (ac != 5 && ac != 6)
    {
        printf("Error!\nWrong amount of arguments!");
        ft_free(vars); 
    }
    ft_error_check(vars, av);
    if (init_comb(vars, av) == 1);
        return (1);
    ft_free(vars);
    return (0);
}