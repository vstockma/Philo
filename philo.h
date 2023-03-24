/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:21:39 by valentin          #+#    #+#             */
/*   Updated: 2023/03/23 15:10:50 by vstockma         ###   ########.fr       */
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
	t_var	*var;
    pthread_t		t;
    int id;
    int stat;
    int eat_counter;
    int time_he_dies;
    pthread_mutex_t	lock;
    pthread_mutex_t	*rf;
	pthread_mutex_t	*lf;
    
}	t_philo;

typedef struct s_var
{
    t_philo *philos;
    pthread_t		*tid;
	int phil_num;
    int t_die;
    int t_eat;
    int t_sleep;
    int count_to_eat;
    int start_time;
    int dead;
    int finish;
    pthread_mutex_t	*forks;
    pthread_mutex_t	lock;
	pthread_mutex_t	printf;

}	t_var;

//main.c
int    init_input(t_var *vars, char **av);

//free.c
void    ft_free(t_var *vars);

//start.c
void    ft_arg5(t_var *vars);
void    ft_arg6(t_var *vars);

//error.c
int	ft_atoi(const char *str);
void    ft_error_check(t_var *vars, char **av);

#endif