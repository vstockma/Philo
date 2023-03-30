/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:39:37 by vstockma          #+#    #+#             */
/*   Updated: 2023/03/30 13:55:50 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_still_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->var->lock);
	if (philo->var->dead != 0 || philo->meals_count == philo->var->count_to_eat)
	{
		philo->done = 1;
		pthread_mutex_unlock(&philo->var->lock);
		return (0);
	}
	if (ft_time() - philo->time_since_last_meal >= philo->var->t_die
		&& philo->var->dead == 0)
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
	while (philo->meals_count != philo->var->count_to_eat && !philo->done)
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
