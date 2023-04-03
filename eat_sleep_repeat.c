/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_repeat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:17:00 by vstockma          #+#    #+#             */
/*   Updated: 2023/04/03 16:01:58 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_sleeping(t_philo *philo)
{
	if (!ft_still_alive(philo))
		return (0);
	ft_handle_state(philo, "is sleeping");
	if (!ft_usleep(philo->var->t_sleep, philo))
		return (0);
	if (!ft_still_alive(philo))
		return (0);
	ft_handle_state(philo, "is thinking");
	ft_usleep(1, philo);
	return (1);
}

int	ft_takes_and_eats(t_philo *philo, int order)
{
	philo->var->forks[philo->right_fork] = philo->id;
	philo->var->forks[philo->left_fork] = philo->id;
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
	if (!ft_still_alive(philo))
		return (0);
	ft_handle_state(philo, "has taken fork");
	ft_handle_state(philo, "has taken fork");
	ft_handle_state(philo, "is eating");
	philo->time_since_last_meal = ft_time();
	if (!ft_usleep(philo->var->t_eat, philo))
		return (0);
	philo->meals_count++;
	return (1);
}

int	ft_is_eating(t_philo *philo)
{
	if (ft_still_alive(philo) == 0)
		return (0);
	ft_lock_and_unlock_forks(philo, 1, philo->id % 2);
	if (philo->var->forks[philo->left_fork] == 0
		&& philo->var->forks[philo->right_fork] == 0)
	{
		if (!ft_takes_and_eats(philo, philo->id % 2))
			return (0);
		ft_let_go_of_forks(philo, philo->id % 2);
		if (!ft_is_sleeping(philo))
			return (0);
		return (1);
	}
	else
	{
		ft_lock_and_unlock_forks(philo, 0, philo->id % 2);
		if (ft_still_alive(philo) == 0)
			return (0);
	}
	return (1);
}

void	ft_lock_and_unlock_forks(t_philo *philo, int flag, int order)
{
	if (flag == 1 && order == 0)
	{
		pthread_mutex_lock(&philo->var->m_forks[philo->right_fork]);
		pthread_mutex_lock(&philo->var->m_forks[philo->left_fork]);
	}
	else if (flag == 1 && order == 1)
	{
		pthread_mutex_lock(&philo->var->m_forks[philo->left_fork]);
		pthread_mutex_lock(&philo->var->m_forks[philo->right_fork]);
	}
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

void	ft_let_go_of_forks(t_philo *philo, int order)
{
	if (order == 1)
	{
		pthread_mutex_lock(&philo->var->m_forks[philo->right_fork]);
		philo->var->forks[philo->right_fork] = 0;
		pthread_mutex_unlock(&philo->var->m_forks[philo->right_fork]);
		pthread_mutex_lock(&philo->var->m_forks[philo->left_fork]);
		philo->var->forks[philo->left_fork] = 0;
		pthread_mutex_unlock(&philo->var->m_forks[philo->left_fork]);
	}
	else if (order == 0)
	{
		pthread_mutex_lock(&philo->var->m_forks[philo->left_fork]);
		philo->var->forks[philo->left_fork] = 0;
		pthread_mutex_unlock(&philo->var->m_forks[philo->left_fork]);
		pthread_mutex_lock(&philo->var->m_forks[philo->right_fork]);
		philo->var->forks[philo->right_fork] = 0;
		pthread_mutex_unlock(&philo->var->m_forks[philo->right_fork]);
	}
}