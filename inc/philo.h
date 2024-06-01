/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:16:30 by ysahraou          #+#    #+#             */
/*   Updated: 2024/06/01 17:04:40 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>

typedef struct s_param
{
    int n_of_philo;
    int t_to_die;
    int t_to_eat;
    int t_to_sleep;
    int n_must_eat;
}               t_param;


long	ft_ato_num(const char *nptr);
int check_args(const char **av);
void ft_err(char *str);
void set_values(const char **av, t_param *param, int ac);
#endif