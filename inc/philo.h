/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:16:30 by ysahraou          #+#    #+#             */
/*   Updated: 2024/06/02 17:05:52 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
#include <pthread.h>

typedef pthread_mutex_t t_mtx;
typedef struct s_philo t_philo;
typedef struct s_data t_data;
typedef struct s_fork t_fork;

struct s_data
{
    int n_of_philo;
    int t_to_die;
    int t_to_eat;
    int t_to_sleep;
    int n_must_eat;
    long    start_s;
    int     end_s;
    t_fork  *forks;
    t_philo *philos;
};

struct s_fork
{
    t_mtx   fork;
    int     id;
};


struct s_philo
{
    int         id;
    pthread_t   t_id;
    long        meals_c;
    int         full;
    t_fork      *right_fork;
    t_fork      *left_fork;
    t_data     *param;
};



long	ft_ato_num(const char *nptr);
int check_args(const char **av);
t_data *set_values(const char **av, int ac);

void ft_err_args(int ac);
void ft_err(char *str);
#endif