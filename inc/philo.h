/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:16:30 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/21 13:17:48 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data	t_data;

struct					s_data
{
	int					n_of_philo;
	int					t_to_die;
	int					t_to_eat;
	int					t_to_sleep;
	int					n_must_eat;
};

long					ft_ato_num(const char *nptr);
int						check_args(const char **av);
t_data					*set_values(const char **av, int ac);

void					ft_err_args(int ac);
void					ft_err(char *str);
#endif