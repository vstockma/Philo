/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:49:02 by vstockma          #+#    #+#             */
/*   Updated: 2023/04/11 10:58:30 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_routine_one_philo(void *arg)
{
	arg = NULL;
	arg++;
	return (NULL);
}

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

void	ft_print_if_meals_count(t_var vars)
{
	int	i;

	i = 0;
	if (vars.nbr_of_times_to_eat == -1)
		return ;
	else if (vars.dead == 0)
		printf("%lld all have eaten %d times\n",
			ft_get_time_in_ms() - vars.start_time, vars.nbr_of_times_to_eat);
}

void	ft_handle_state(t_philo *philo, char *state)
{
	pthread_mutex_lock(&philo->var->lock);
	pthread_mutex_lock(&philo->var->printf);
	if (philo->meals_count != philo->var->nbr_of_times_to_eat && !philo->done
		&& !philo->var->dead)
	{
		printf("%lld %d %s\n", (ft_get_time_in_ms() - philo->var->start_time),
			philo->id, state);
	}
	pthread_mutex_unlock(&philo->var->printf);
	pthread_mutex_unlock(&philo->var->lock);
}
