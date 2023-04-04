/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_repeat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:17:00 by vstockma          #+#    #+#             */
/*   Updated: 2023/04/04 13:29:17 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_is_sleeping(t_philo *philo)
{
// check if the philosopher is still alive and meals count is not reached yet
if (!ft_check_if_all_alive(philo))
return (0);
// change the state to "is sleeping"
ft_handle_state(philo, "is sleeping");
// make the philosopher sleep for a specified amount of time
if (!ft_usleep(philo->var->time_to_sleep, philo))
return (0);
// check if the philosopher is still alive and meals count is not reached yet
if (!ft_check_if_all_alive(philo))
return (0);
// change the state to "is thinking"
ft_handle_state(philo, "is thinking");
// sleep for a short time to avoid the threads starving each other
ft_usleep(1, philo);
return (1);
}

int	ft_takes_and_eats(t_philo *philo, int order)
{
	// The philosopher takes the forks.
	philo->var->forks[philo->right_fork] = philo->id;
	philo->var->forks[philo->left_fork] = philo->id;
	// Depending on the order, the philosopher releases the forks in a specific order.
	if (order == 1)
	{
		pthread_mutex_unlock(&philo->var->m_forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->var->m_forks[philo->left_fork]);
	}
	else if (order == 0)
	{
		pthread_mutex_unlock(&philo->var->m_forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->var->m_forks[philo->right_fork]);
	}
	// Checks if all the philosophers are alive.
	if (!ft_check_if_all_alive(philo))
		return (0);
	// Print message about taking forks.
	ft_handle_state(philo, "has taken fork");
	ft_handle_state(philo, "has taken fork");
	// Print message about eating.
	ft_handle_state(philo, "is eating");
	// Update time since last meal.
	philo->time_since_last_meal = ft_get_time_in_ms();
	// Sleep for the specified time to eat.
	if (!ft_usleep(philo->var->time_to_eat, philo))
		return (0);
	// Increment meal count.
	philo->meals_count++;
	return (1);
}

int	ft_is_eating(t_philo *philo)
{
	// check if all philosophers are alive
	if (ft_check_if_all_alive(philo) == 0)
		return (0);
	// lock forks for the current philosopher
	ft_lock_and_unlock_forks(philo, 1, philo->id % 2);
	// check if the forks on both sides are available
	if (philo->var->forks[philo->left_fork] == 0
		&& philo->var->forks[philo->right_fork] == 0)
	{
		// if yes, take and eat with the lower-numbered fork first
		if (!ft_takes_and_eats(philo, philo->id % 2))
			return (0);
		// release forks
		ft_let_go_of_forks(philo, philo->id % 2);
		// if there is no error, philosopher is sleeping
		if (!ft_is_sleeping(philo))
			return (0);
		return (1);
	}
	else
	{
		// if the forks are not available, unlock the forks
		ft_lock_and_unlock_forks(philo, 0, philo->id % 2);
		// check if all philosophers are alive
		if (ft_check_if_all_alive(philo) == 0)
			return (0);
	}
	return (1);
}

// The purpose of this function is to prevent the possibility of two threads attempting
// to grab the same forks simultaneously, which could result in a deadlock or data race.
// It takes two arguments: flag, which determines whether the forks should be locked or unlocked,
// and order, which determines the order in which the forks should be locked or unlocked.
// The function uses a mutex to lock or unlock each fork, depending on the order argument.
void	ft_lock_and_unlock_forks(t_philo *philo, int flag, int order)
{
	// if flag is 1 and order is 0, lock the right fork first then the left fork
	if (flag == 1 && order == 0)
	{
		pthread_mutex_lock(&philo->var->m_forks[philo->right_fork]);
		pthread_mutex_lock(&philo->var->m_forks[philo->left_fork]);
	}
	// if flag is 1 and order is 1, lock the left fork first then the right fork
	else if (flag == 1 && order == 1)
	{
		pthread_mutex_lock(&philo->var->m_forks[philo->left_fork]);
		pthread_mutex_lock(&philo->var->m_forks[philo->right_fork]);
	}
	// if flag is 0, unlock the forks according to the order
	else
	{
		if (order == 0)
		{
			pthread_mutex_unlock(&philo->var->m_forks[philo->left_fork]);
			pthread_mutex_unlock(&philo->var->m_forks[philo->right_fork]);
		}
		else
		{
			pthread_mutex_unlock(&philo->var->m_forks[philo->right_fork]);
			pthread_mutex_unlock(&philo->var->m_forks[philo->left_fork]);
		}
	}
}

// Overall, the ft_let_go_of_forks function ensures that the forks used by a
// philosopher are released in the correct order to prevent deadlocks and to ensure
// that other philosophers can access the forks in a consistent manner.
void	ft_let_go_of_forks(t_philo *philo, int order)
{
	// If the order is 1, unlock the right fork first, then the left fork
	if (order == 1)
	{
		pthread_mutex_lock(&philo->var->m_forks[philo->right_fork]); // Lock the right fork
		philo->var->forks[philo->right_fork] = 0; // Release the right fork by setting its value to 0
		pthread_mutex_unlock(&philo->var->m_forks[philo->right_fork]); // Unlock the right fork
		pthread_mutex_lock(&philo->var->m_forks[philo->left_fork]); // Lock the left fork
		philo->var->forks[philo->left_fork] = 0; // Release the left fork by setting its value to 0
		pthread_mutex_unlock(&philo->var->m_forks[philo->left_fork]); // Unlock the left fork
	}
	// If the order is 0, unlock the left fork first, then the right fork
	else if (order == 0)
	{
		pthread_mutex_lock(&philo->var->m_forks[philo->left_fork]); // Lock the left fork
		philo->var->forks[philo->left_fork] = 0; // Release the left fork by setting its value to 0
		pthread_mutex_unlock(&philo->var->m_forks[philo->left_fork]); // Unlock the left fork
		pthread_mutex_lock(&philo->var->m_forks[philo->right_fork]); // Lock the right fork
		philo->var->forks[philo->right_fork] = 0; // Release the right fork by setting its value to 0
		pthread_mutex_unlock(&philo->var->m_forks[philo->right_fork]); // Unlock the right fork
	}
}
