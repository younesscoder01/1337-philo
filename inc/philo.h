/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:16:30 by ysahraou          #+#    #+#             */
/*   Updated: 2024/10/02 09:57:18 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef pthread_mutex_t	t_mt;

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define WHITE "\033[0;37m"
#define BLUE "\033[0;34m"
typedef struct s_data
{
	int					n_of_philo;
	int					t_to_die;
	int					t_to_eat;
	int					t_to_sleep;
	int					n_must_eat;
}						t_data;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	time_t				start_t;
	time_t				last_meal;
	int					n_of_philo;
	int					t_to_die;
	int					t_to_eat;
	int					t_to_sleep;
	int					n_must_eat;
	int					full;
	bool				*died;
	t_mt				*died_m;
	t_mt				*id_m;
	t_mt				*last_meal_m;
	t_mt				*full_m;
	t_mt				*start;
	t_mt				*l_fork;
	t_mt				*r_fork;
}						t_philo;

typedef struct s_mxt
{
	t_mt				*died_m;
	t_mt				*start;
	t_mt				*id_m;
	t_mt				*last_meal_m;
	t_mt				*full_m;
}						t_mxt;

long					ft_ato_num(const char *nptr);
int						check_args(const char **av);
t_data					*set_values(const char **av, int ac);
int						check_died(t_philo *philo);
int						check_meals(t_philo *philo);
void					ft_err_args(int ac);
void					ft_err(char *str);
void					sleep_m(time_t num);
time_t					get_time_millsec(void);
time_t					get_start(t_philo *philo);
int						get_id(t_philo *philo);
time_t					get_last_meal(t_philo *philo);
void					print_fork(t_philo *philo);
void					print_sleep(t_philo *philo);
void					eat(t_philo *philo);
void					destroy_mtx(t_philo *ph, t_data *data);
void					init_data(t_philo *ph, t_data *data);
void					init_forks(t_philo *ph, t_data *data);
void					init_mtx(t_philo *ph, t_data *data);
#endif