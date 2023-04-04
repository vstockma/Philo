/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:49:02 by vstockma          #+#    #+#             */
/*   Updated: 2023/04/04 12:54:53 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// This is just the routine function if the number of Philosophers is 1,
// but it doesn't d anything
void	*ft_routine_one_philo(void *arg)
{
	arg = NULL;
	arg++;
	return (NULL);
}

// This function is specific if the number of Philosophers is 1,
// because the subject wants one thread for each Philosopher
// even if there is only one
void	ft_one_philo(t_var *vars)
{
	pthread_t	t1;

	pthread_create(&t1, NULL, ft_routine_one_philo, NULL);
	printf("0 1 has taken fork\n");
	usleep(vars->time_to_die);
	printf("%d died\n", vars->time_to_die);
	pthread_join(t1, NULL);
	exit(0);
}

void	ft_check_meals_count(t_var vars)
{
	int	i;

	i = 0;
	// Check if the number of times each philosopher should eat is set to -1
	// If it is, then there is no need to check the meals count
	if (vars.nbr_of_times_to_eat == -1)
		return ;
	// Check the meals count of each philosopher
	while (i < vars.nbr_of_philos)
	{
		// If any philosopher has not eaten the required number of times, return
		if (vars.philos[i].meals_count != vars.nbr_of_times_to_eat)
			return ;
		i++;
	}
	// If all philosophers have eaten the required number of times, print a message
	// indicating that all have eaten the required number of times
	pthread_mutex_lock(&vars.philos->var->printf);
	printf("%lld all have eaten %d times\n",
		ft_get_time_in_ms() - vars.start_time, vars.nbr_of_times_to_eat);
	pthread_mutex_unlock(&vars.philos->var->printf);
}

void	ft_handle_state(t_philo *philo, char *state)
{
	// Lock the mutex protecting the philosopher's t_var struct
	pthread_mutex_lock(&philo->var->lock);
	// Lock the mutex protecting the standard output
	pthread_mutex_lock(&philo->var->printf);
	// If the philosopher has not completed their required number of meals, is not already done,
	// and no other philosopher has died, print the current state of the philosopher along with
	// the current time and the philosopher's ID
	if (philo->meals_count != philo->var->nbr_of_times_to_eat && !philo->done
		&& !philo->var->dead)
	{
		printf("%lld %d %s\n", (ft_get_time_in_ms() - philo->var->start_time),
			philo->id, state);
	}
	// Release the mutex protecting the standard output
	pthread_mutex_unlock(&philo->var->printf);
	// Release the mutex protecting the philosopher's t_var struct
	pthread_mutex_unlock(&philo->var->lock);
}
