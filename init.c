/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:41:56 by valentin          #+#    #+#             */
/*   Updated: 2023/04/04 13:11:02 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// This function initializes each element of the t_var struct
// and assigns the right value depending on the arguments given
int	ft_init_input(t_var *vars, char **av)
{
	// number of Philosopher
	vars->nbr_of_philos = ft_atoi(av[1]);
	// time till he dies
	vars->time_to_die = ft_atoi(av[2]);
	// time he needs to eat
	vars->time_to_eat = ft_atoi(av[3]);
	// time he needs to sleep
	vars->time_to_sleep = ft_atoi(av[4]);
	if (vars->nbr_of_philos < 1 || vars->nbr_of_philos > 200
		|| vars->time_to_die < 0 || vars->time_to_eat < 0
		|| vars->time_to_sleep < 0)
		return (1);
	// if there is a fifth argument it gets assigned to the 
	// number of times each Philosopher has to eat
	if (av[5])
		vars->nbr_of_times_to_eat = ft_atoi(av[5]);
	else
		vars->nbr_of_times_to_eat = -1;
	// sets the start time to the current time
	vars->start_time = ft_get_time_in_ms();
	// initializes the dead flag to 0
	vars->dead = 0;
	return (0);
}

// This function calls three other functions which initialize
// mutexes, allocs mem, initializes every value for each Philosopher
// and initializes one thread per Philosopher
int	ft_init_all(t_var *vars)
{
	int	i;

	i = 0;
	if (ft_init_and_malloc(vars) == 0)
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

int	ft_init_and_malloc(t_var *vars)
{
	int	i;

	i = 0;
	// allocate memory for t_philo struct array
	vars->philos = malloc(sizeof(t_philo) * vars->nbr_of_philos);
	// allocate memory for mutex array
	vars->m_forks = malloc(sizeof(pthread_mutex_t) * vars->nbr_of_philos);
	// allocate memory for forks array
	vars->forks = malloc(sizeof(int) * vars->nbr_of_philos);
	// check if any of the allocations failed
	if (!vars->philos || !vars->m_forks || !vars->forks)
		return (0);
	// initialize each mutex in the array
	while (i < vars->nbr_of_philos)
	{
		pthread_mutex_init(&vars->m_forks[i], NULL);
		i++;
	}
	// initialize the printf mutex
	pthread_mutex_init(&vars->printf, NULL);
	// initialize the lock mutex
	pthread_mutex_init(&vars->lock, NULL);
	return (1);
}

void	ft_init_philos(t_philo *philo, int i)
{
	// set the philosopher's id to the index i incremented by 1
	philo->id = i + 1;
	// set the index of the left fork of the philosopher to i
	philo->left_fork = i;
	// set the index of the right fork of the philosopher to (i + 1) % number of philosophers
	// This ensures that the last philosopher's right fork will be the first philosopher's left fork.
	philo->right_fork = (i + 1) % philo->var->nbr_of_philos;
	// set the state of the philosopher's fork to not in use
	philo->var->forks[i] = 0;
	// set the state of the philosopher to not done eating
	philo->done = 0;
	// set the number of meals the philosopher has eaten to 0
	philo->meals_count = 0;
	// set the time since the philosopher's last meal to the start time of the simulation
	philo->time_since_last_meal = philo->var->start_time;
}

// This function creates a thread for each philosopher and calls ft_routine function
// using the address of the corresponding t_philo struct as argument
// i.e. &vars->philos[i]. Then it waits for each thread to finish using pthread_join.
int	ft_init_threads(t_var *vars)
{
	int	i;
	// Create threads for each philosopher
	i = 0;
	while (i < vars->nbr_of_philos)
	{
		// pthread_create creates a new thread and assigns it a thread number
		// The thread runs the function ft_routine with a pointer to the philosopher struct
		pthread_create(&vars->philos[i].thread_nbr, NULL, ft_routine,
			(void *)&vars->philos[i]);
		i++;
	}
	// Wait for all threads to finish executing
	i = 0;
	while (i < vars->nbr_of_philos)
	{
		// pthread_join waits for the thread with the specified thread number to finish
		// NULL is passed as the second argument since we are not interested in the thread's return value
		if (pthread_join(vars->philos[i].thread_nbr, NULL) != 0)
		{
			// If an error occurs while waiting for the thread to finish, return 0
			printf("Error joining threads!\n");
			return (0);
		}
		i++;
	}
	// If all threads finished executing successfully, return 1
	return (1);
}
