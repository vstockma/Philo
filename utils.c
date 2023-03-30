/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:30:13 by vstockma          #+#    #+#             */
/*   Updated: 2023/03/30 13:05:30 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_usleep(unsigned int time, t_philo *philo)
{
	long long	current_time;

	current_time = ft_time();
	if (!ft_still_alive(philo))
		return (0);
	while ((ft_time() - current_time) < (long long)time)
	{
		if (!ft_still_alive(philo))
			return (0);
		usleep(100);
	}
	return (1);
}

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

void	ft_free_destroy(t_var *vars)
{
	int	i;

	i = 0;
	while (i < vars->phil_num)
	{
		pthread_mutex_destroy(&vars->m_forks[i]);
		i++;
	}
	pthread_mutex_destroy(&vars->printf);
	pthread_mutex_destroy(&vars->lock);
	free(vars->m_forks);
	free(vars->forks);
	free(vars->philos);
	free(vars);
	exit(0);
}
