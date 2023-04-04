/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:39:37 by vstockma          #+#    #+#             */
/*   Updated: 2023/04/04 13:15:42 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// This function is used to check if a philosopher is still alive, by checking if 
// it has reached the maximum number of meals or if its time since last meal
// is greater than the time allowed for dying.

int	ft_check_if_all_alive(t_philo *philo)
{
	// A mutex is locked in order to avoid possible race conditions.
	pthread_mutex_lock(&philo->var->lock);
	// If the philosopher is dead, or has reached the maximum number of meals,
	// it's marked as done and the function returns 0.
	if (philo->var->dead != 0 || philo->meals_count == philo->var->nbr_of_times_to_eat)
	{
		philo->done = 1;
		pthread_mutex_unlock(&philo->var->lock);
		return (0);
	}
	// If the time since the philosopher's last meal is greater than the time allowed
	// for dying and the philosopher is not marked as dead, it changes its state to "died",
	// it's marked as done and dead, and the function returns 0.
	if (ft_get_time_in_ms() - philo->time_since_last_meal >= philo->var->time_to_die
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
	// If none of the above conditions is met, the mutex is unlocked and the
	// function returns 1.
	pthread_mutex_unlock(&philo->var->lock);
	return (1);
}

// This function is the routine for each philosopher thread
// It takes a void pointer argument that is casted to t_philo struct pointer

void	*ft_routine(void *arg)
{
	// Cast the void pointer to t_philo struct pointer
	t_philo	*philo;
	philo = (t_philo *)arg;
	// The philosopher will keep running its routine until they have eaten the
	// required amount of times or someone has died
	while (philo->meals_count != philo->var->nbr_of_times_to_eat && !philo->done)
	{
		// The philosopher acquires the lock that is protecting the state of
		// the system
		pthread_mutex_lock(&philo->var->lock);
		// If nobody has died, the philosopher releases the lock and checks if
		// they can start eating
		if (!philo->var->dead)
		{
			pthread_mutex_unlock(&philo->var->lock);
			// If the philosopher can start eating, they call the function to
			// simulate eating and check if there were any errors
			if (ft_is_eating(philo) == 0)
				return (NULL);
		}
		// If someone has died, the philosopher releases the lock and returns
		// immediately
		else
		{
			pthread_mutex_unlock(&philo->var->lock);
			return (NULL);
		}
	}
	// If the philosopher has eaten the required amount of times, or someone
	// has died, they return
	return (NULL);
}
