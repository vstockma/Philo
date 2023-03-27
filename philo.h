/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:21:39 by valentin          #+#    #+#             */
/*   Updated: 2023/03/27 13:42:01 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>


typedef struct s_philo
{
    pthread_t		t_nbr;
    int id;
    int left_fork;
    int right_fork;
    int meals_count;
    int done;
    long long time_since_last_meal;
	t_var	*var;
}	t_philo;

typedef struct s_var
{
    t_philo *philos;
    pthread_mutex_t	*m_forks;
    pthread_mutex_t	lock;
	pthread_mutex_t	printf;
	int phil_num;
    int t_die;
    int t_eat;
    int t_sleep;
    int count_to_eat;
    int start_time;
    int dead;
    int finish;
    int *forks;
}	t_var;

//philo.c
int    init_input(t_var *vars, char **av);

//init.c
int    init_comb(t_var *vars, char **av);
int    init_input(t_var *vars, char **av);
int init_and_malloc(t_var *vars);
void init_philos(t_philo *philo, int i);
int init_threads(t_var *vars);

//action.c
void ft_routine(void *arg);

//extra.c
int	ft_atoi(const char *str);
void    ft_error_check(t_var *vars, char **av);

//free.c
void    ft_free_destroy(t_var *vars);

//error.c
int	ft_atoi(const char *str);
void    ft_error_check(t_var *vars, char **av);

#endif