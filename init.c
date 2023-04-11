/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:41:56 by valentin          #+#    #+#             */
/*   Updated: 2023/04/11 11:15:42 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_input(t_var *vars, char **av)
{
	vars->nbr_of_philos = ft_atoi(av[1]);
	vars->time_to_die = ft_atoi(av[2]);
	vars->time_to_eat = ft_atoi(av[3]);
	vars->time_to_sleep = ft_atoi(av[4]);
	if (vars->nbr_of_philos < 1 || vars->nbr_of_philos > 200
		|| vars->time_to_die < 0 || vars->time_to_eat < 0
		|| vars->time_to_sleep < 0)
		return (1);
	if (av[5])
		vars->nbr_of_times_to_eat = ft_atoi(av[5]);
	else
		vars->nbr_of_times_to_eat = -1;
	vars->start_time = ft_get_time_in_ms();
	vars->dead = 0;
	return (0);
}

int	ft_init_all(t_var *vars)
{
	int	i;

	i = 0;
	if (ft_init_malloc_and_mutex(vars) == 0)
		return (1);
	while (i < vars->nbr_of_philos)
	{
		vars->philos[i].var = vars;
		ft_init_philos(&vars->philos[i], i);
		i++;
	}
	if (!ft_init_threads(vars))
		return (0);
	return (1);
}

int	ft_init_malloc_and_mutex(t_var *vars)
{
	int	i;

	i = 0;
	vars->philos = malloc(sizeof(t_philo) * vars->nbr_of_philos);
	vars->m_forks = malloc(sizeof(pthread_mutex_t) * vars->nbr_of_philos);
	vars->forks = malloc(sizeof(int) * vars->nbr_of_philos);
	if (!vars->philos || !vars->m_forks || !vars->forks)
		return (0);
	while (i < vars->nbr_of_philos)
	{
		pthread_mutex_init(&vars->m_forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&vars->printf, NULL);
	pthread_mutex_init(&vars->lock, NULL);
	return (1);
}

void	ft_init_philos(t_philo *philo, int i)
{
	philo->id = i + 1;
	philo->left_fork = i;
	philo->right_fork = (i + 1) % philo->var->nbr_of_philos;
	philo->var->forks[i] = 0;
	philo->done = 0;
	philo->meals_count = 0;
	philo->time_since_last_meal = philo->var->start_time;
}

int	ft_init_threads(t_var *vars)
{
	int	i;

	i = 0;
	while (i < vars->nbr_of_philos)
	{
		pthread_create(&vars->philos[i].thread_nbr, NULL, ft_routine,
			(void *)&vars->philos[i]);
		i++;
	}
	i = 0;
	while (i < vars->nbr_of_philos)
	{
		if (pthread_join(vars->philos[i].thread_nbr, NULL) != 0)
		{
			printf("Error joining threads!\n");
			return (0);
		}
		i++;
	}
	return (1);
}
