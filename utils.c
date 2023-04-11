/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:30:13 by vstockma          #+#    #+#             */
/*   Updated: 2023/04/04 12:32:10 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_get_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_usleep(unsigned int time, t_philo *philo)
{
	long long	current_time;

	current_time = ft_get_time_in_ms();
	if (!ft_check_if_all_alive(philo))
		return (0);
	while ((ft_get_time_in_ms() - current_time) < (long long)time)
	{
		if (!ft_check_if_all_alive(philo))
			return (0);
		usleep(100);
	}
	return (1);
}

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
