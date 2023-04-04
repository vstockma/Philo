/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:21:52 by valentin          #+#    #+#             */
/*   Updated: 2023/04/04 12:22:57 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_var	vars;

	if (ac != 5 && ac != 6)
	{
		printf("Error!\nWrong amount of arguments!");
		return (1);
	}
	ft_check_if_args_are_num(av);
	if (ft_init_input(&vars, av) != 0)
	{
		printf("Error!\nWrong values for input!");
		return (1);
	}
	if (vars.nbr_of_philos == 1)
		ft_one_philo(&vars);
	if (!ft_init_all(&vars))
		return (1);
	ft_check_meals_count(vars);
	ft_free_destroy(&vars);
	return (0);
}
