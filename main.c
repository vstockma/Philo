/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:21:52 by valentin          #+#    #+#             */
/*   Updated: 2023/04/11 13:14:18 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_if_all_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->var->lock);
	if (philo->var->dead != 0
		|| philo->meals_count == philo->var->nbr_of_times_to_eat)
	{
		philo->done = 1;
		pthread_mutex_unlock(&philo->var->lock);
		return (0);
	}
	if (ft_get_time_in_ms() - philo->time_since_last_meal
		>= philo->var->time_to_die && philo->var->dead == 0)
	{
		pthread_mutex_unlock(&philo->var->lock);
		ft_handle_state(philo, "died");
		pthread_mutex_lock(&philo->var->lock);
		philo->done = 1;
		philo->var->dead = 1;
		pthread_mutex_unlock(&philo->var->lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->var->lock);
	return (1);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->meals_count != philo->var->nbr_of_times_to_eat
		&& !philo->done)
	{
		pthread_mutex_lock(&philo->var->lock);
		if (!philo->var->dead)
		{
			pthread_mutex_unlock(&philo->var->lock);
			if (ft_is_eating(philo) == 0)
				return (NULL);
		}
		else
		{
			pthread_mutex_unlock(&philo->var->lock);
			return (NULL);
		}
	}
	return (NULL);
}

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
	ft_print_if_meals_count(vars);
	ft_free_destroy(&vars);
	return (0);
}
