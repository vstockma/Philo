/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:21:39 by valentin          #+#    #+#             */
/*   Updated: 2023/02/24 13:19:56 by valentin         ###   ########.fr       */
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


typedef struct s_var
{
	int phil_num;
    int t_die;
    int t_eat;
    int t_sleep;
    int count_to_eat;

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