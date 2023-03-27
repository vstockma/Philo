/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:39:37 by vstockma          #+#    #+#             */
/*   Updated: 2023/03/27 16:17:54 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_eat_count(t_var *vars)
{
	int	i;

	i = 0;
	if (vars->count_to_eat == -1)
		return ;
	while (i < vars->phil_num)
	{
		if (vars->philos[i].meals_count != vars->count_to_eat)
			return ;
		i++;
	}
	pthread_mutex_lock(&vars->philos->var->printf);
	printf("%lld all have eaten %d times\n", ft_time() - vars->start_time,
			vars->count_to_eat);
	pthread_mutex_unlock(&vars->philos->var->printf);
}

void	ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while ()
	{
	}
	return (NULL);
}
