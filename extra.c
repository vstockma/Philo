/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:49:02 by vstockma          #+#    #+#             */
/*   Updated: 2023/03/27 16:17:59 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	ft_error_check(t_var *vars, char **av)
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
				ft_free(vars);
			}
			i++;
		}
		j++;
	}
}

long long	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_free_destroy(t_var *vars)
{
	int i;

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