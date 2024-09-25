/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:16:30 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/23 15:16:36 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>

typedef pthread_mutex_t pt_mt;
typedef struct s_data	t_data;

struct					s_data
{
	int					n_of_philo;
	int					t_to_die;
	int					t_to_eat;
	int					t_to_sleep;
	int					n_must_eat;
};

typedef struct			s_philo
{
	pthread_t	thread;
	int id;
	time_t		start_t;
	time_t		last_meal;
	int					n_of_philo;
	int					t_to_die;
	int					t_to_eat;
	int					t_to_sleep;
	int					n_must_eat;
	int					full;
	bool				*died;
	pt_mt				*died_m;
	pt_mt				*l_fork;
	pt_mt				*r_fork;
}						t_philo;

long					ft_ato_num(const char *nptr);
int						check_args(const char **av);
t_data					*set_values(const char **av, int ac);
int check_died(t_philo *philo);
int check_meals(t_philo *philo);
void					ft_err_args(int ac);
void					ft_err(char *str);
#endif