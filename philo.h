/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:21:39 by valentin          #+#    #+#             */
/*   Updated: 2023/04/11 11:24:53 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread_nbr;
	int				id;
	int				left_fork;
	int				right_fork;
	int				meals_count;
	int				done;
	long long		time_since_last_meal;
	struct s_var	*var;
}					t_philo;

typedef struct s_var
{
	t_philo			*philos;
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	printf;
	int				nbr_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				nbr_of_times_to_eat;
	long long		start_time;
	int				*forks;
	int				dead;
}					t_var;

//main.c
int					ft_check_if_all_alive(t_philo *philo);
void				*ft_routine(void *arg);

//init.c
int					ft_init_all(t_var *vars);
int					ft_init_input(t_var *vars, char **av);
int					ft_init_malloc_and_mutex(t_var *vars);
void				ft_init_philos(t_philo *philo, int i);
int					ft_init_threads(t_var *vars);

//eat_sleep_repeat.c
int					ft_is_sleeping(t_philo *philo);
int					ft_he_eats(t_philo *philo, int order);
int					ft_is_eating(t_philo *philo);
void				ft_lock_and_unlock_forks(t_philo *philo, int flag,
						int order);
void				ft_let_go_of_forks(t_philo *philo, int order);

//extra.c
void				*ft_routine_one_philo(void *arg);
void				ft_one_philo(t_var *vars);
void				ft_print_if_meals_count(t_var vars);
void				ft_handle_state(t_philo *philo, char *state);

//utils.c
long long			ft_get_time_in_ms(void);
int					ft_usleep(unsigned int time, t_philo *philo);
void				ft_check_if_args_are_num(char **av);
int					ft_atoi(const char *str);
void				ft_free_destroy(t_var *vars);

#endif