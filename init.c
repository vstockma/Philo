/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:41:56 by valentin          #+#    #+#             */
/*   Updated: 2023/03/27 16:18:03 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_comb(t_var *vars, char **av)
{
	int	i;

	i = 0;
	if (init_input(vars, av) != 0)
	{
		printf("Error!\nWrong values for input!");
		return (1);
	}
	if (!init_and_malloc(vars))
		return (0);
	while (i < vars->phil_num)
	{
		vars->philos[i].var = vars;
		init_philos(&vars->philos[i], i);
		i++;
	}
	if (!init_threads(vars))
		return (0);
	return (1);
}

int	init_input(t_var *vars, char **av)
{
	vars->phil_num = ft_atoi(av[1]);
	vars->t_die = ft_atoi(av[2]);
	vars->t_eat = ft_atoi(av[3]);
	vars->t_sleep = ft_atoi(av[4]);
	if (vars->phil_num < 1 || vars->phil_num > 200 || vars->t_die < 0 ||
		vars->t_eat < 0 || vars->t_sleep < 0)
		return (1);
	if (av[5])
		vars->count_to_eat = ft_atoi(av[5]);
	else
		vars->count_to_eat = -1;
	vars->start_time = current_timestamp();
	vars->dead = 0;
	vars->finish = 0;
	pthread_mutex_init(&vars->lock, NULL);
	return (0);
}

int	init_and_malloc(t_var *vars)
{
	int	i;

	i = 0;
	vars->m_forks = malloc(sizeof *vars->m_forks * vars->phil_num);
	vars->philos = malloc(sizeof *vars->philos * vars->phil_num);
	vars->forks = malloc(sizeof *vars->forks * vars->phil_num);
	if (!vars->philos || !vars->m_forks || !vars->forks)
	{
		printf("Allocation Error!");
		return (0);
	}
	while (i < vars->phil_num)
	{
		pthread_mutex_init(&vars->m_forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&vars->printf, NULL);
	pthread_mutex_init(&vars->lock, NULL);
	return (1);
}

void	init_philos(t_philo *philo, int i)
{
	philo->id = i + 1;
	philo->left_fork = i;
	philo->right_fork = (i + 1) % philo->var->phil_num;
	philo->var->forks[i] = 0;
	philo->done = 0;
	philo->meals_count = 0;
	philo->time_since_last_meal = philo->var->start_time;
}

int	init_threads(t_var *vars)
{
	int	i;

	i = 0;
	while (i < vars->phil_num)
	{
		pthread_create(&vars->philos[i].t_nbr, NULL, ft_routine,
				(void *)&vars->philos[i]);
		i++;
	}
	i = 0;
	while (i < vars->phil_num)
	{
		if (pthread_join(vars->philos[i].t_nbr, NULL) != 0)
			;
		{
			printf("Error joining threads!\n");
			return (0);
		}
		i++;
	}
	return (1);
}
