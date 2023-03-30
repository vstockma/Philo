/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:49:02 by vstockma          #+#    #+#             */
/*   Updated: 2023/03/30 13:50:59 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_fill_routine(void *arg)
{
	arg = NULL;
	arg++;
	return (NULL);
}

void	ft_one_philo(t_var *vars)
{
	pthread_t	t1;
	pthread_create(&t1, NULL, ft_fill_routine, NULL);
	printf("0 1 has taken fork\n");
	usleep(vars->t_die);
	printf("%d died\n", vars->t_die);
	pthread_join(t1, NULL);
	exit(0);
}

void	check_eat_count(t_var vars)
{
	int	i;

	i = 0;
	if (vars.count_to_eat == -1)
		return ;
	while (i < vars.phil_num)
	{
		if (vars.philos[i].meals_count != vars.count_to_eat)
			return ;
		i++;
	}
	pthread_mutex_lock(&vars.philos->var->printf);
	printf("%lld all have eaten %d times\n", ft_time() - vars.start_time,
		vars.count_to_eat);
	pthread_mutex_unlock(&vars.philos->var->printf);
}

void	ft_handle_state(t_philo *philo, char *state)
{
	pthread_mutex_lock(&philo->var->lock);
	pthread_mutex_lock(&philo->var->printf);
	if (philo->meals_count != philo->var->count_to_eat && !philo->done
		&& !philo->var->dead)
	{
		printf("%lld %d %s\n", (ft_time() - philo->var->start_time), philo->id,
			state);
	}
	pthread_mutex_unlock(&philo->var->printf);
	pthread_mutex_unlock(&philo->var->lock);
}

void	ft_error_check(char **av)
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
