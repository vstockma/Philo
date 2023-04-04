/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:30:13 by vstockma          #+#    #+#             */
/*   Updated: 2023/04/04 12:48:08 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// This function returns the current time in milliseconds.
long long	ft_get_time_in_ms(void)
{
	struct timeval	time;

	// Get the current time
	gettimeofday(&time, NULL);

	// Convert the time to milliseconds and return it
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

// This function sleeps for the specified amount of time using a
// loop that constantly checks if all philosophers are alive. If any
// philosopher is dead, it returns 0 and exits the loop early. If all
// philosophers are alive and the specified time has passed, it returns 1.
int	ft_usleep(unsigned int time, t_philo *philo)
{
    long long	current_time;

    // get the current time in milliseconds
    current_time = ft_get_time_in_ms();

    // check if all philosophers are alive before sleeping
    if (!ft_check_if_all_alive(philo))
        return (0);

    // wait loop that checks if the specified time has passed
    while ((ft_get_time_in_ms() - current_time) < (long long)time)
    {
        // check if all philosophers are alive before continuing to sleep
        if (!ft_check_if_all_alive(philo))
            return (0);
        // sleep for a short time
        usleep(100);
    }
    // if all philosophers are still alive after sleeping, return 1
    return (1);
}

// This function checks if each argument contains anything else than numbers
void	ft_check_if_args_are_num(char **av)
{
	int	i;
	int	j;

	j = 1;
	while (av[j])
	{
		i = 0;
		while (av[j][i])
		{
			if (av[j][i] < '0' || av[j][i] > '9')
			{
				printf("Error!\nSomething is wrong with the input");
				exit(1);
			}
			i++;
		}
		j++;
	}
}

//This function converts each argument from a string to an int
int	ft_atoi(const char *str)
{
	int		i;
	int		a;
	long	value;

	value = 0;
	i = 0;
	a = 1;
	while (str[i] && ((str[i] >= 7 && str[i] <= 13) || str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			a = -a;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		value = 10 * value + (str[i] - 48);
		i++;
		if (value * a < -2147483648)
			return (0);
		else if (value * a > 2147483647)
			return (-1);
	}
	return ((int)value * a);
}

//This function frees all allocated memory and destroy mutexes
void	ft_free_destroy(t_var *vars)
{
	int	i;

	i = 0;
	while (i < vars->nbr_of_philos)
	{
		pthread_mutex_destroy(&vars->m_forks[i]);
		i++;
	}
	pthread_mutex_destroy(&vars->printf);
	pthread_mutex_destroy(&vars->lock);
	free(vars->m_forks);
	free(vars->forks);
	free(vars->philos);
	exit(0);
}
