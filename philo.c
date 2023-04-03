/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:21:52 by valentin          #+#    #+#             */
/*   Updated: 2023/04/03 16:13:37 by vstockma         ###   ########.fr       */
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
	ft_error_check(av);
	if (init_input(&vars, av) != 0)
	{
		printf("Error!\nWrong values for input!");
		return (1);
	}
	if (vars.phil_num == 1)
		ft_one_philo(&vars);
	if (!init_comb(&vars))
		return (1);
	check_eat_count(vars);
	ft_free_destroy(&vars);
	return (0);
}
