/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:07:45 by ysahraou          #+#    #+#             */
/*   Updated: 2024/10/08 15:10:38 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_mtx(t_philo *ph, t_data *data, int i)
{
	t_mxt	mxt;

	i = 0;
	mxt.died_m = malloc(sizeof(t_mt));
	mxt.start = malloc(sizeof(t_mt));
	mxt.id_m = malloc(sizeof(t_mt));
	mxt.last_meal_m = malloc(sizeof(t_mt));
	mxt.full_m = malloc(sizeof(t_mt));
	mxt.print = malloc(sizeof(t_mt));
	pthread_mutex_init(mxt.died_m, 0);
	pthread_mutex_init(mxt.start, 0);
	pthread_mutex_init(mxt.id_m, 0);
	pthread_mutex_init(mxt.last_meal_m, 0);
	pthread_mutex_init(mxt.full_m, 0);
	pthread_mutex_init(mxt.print, 0);
	while (data->n_of_philo > i)
	{
		ph[i].died_m = mxt.died_m;
		ph[i].start = mxt.start;
		ph[i].id_m = mxt.id_m;
		ph[i].last_meal_m = mxt.last_meal_m;
		ph[i].full_m = mxt.full_m;
		ph[i].print = mxt.print;
		i++;
	}
}

void	setup_died(t_philo *ph, t_data *data)
{
	int		i;
	bool	*died;

	i = 0;
	died = malloc(sizeof(bool));
	*died = 0;
	while (data->n_of_philo > i)
	{
		ph[i].died = died;
		i++;
	}
}

void	init_data(t_philo *ph, t_data *data, t_mt *mtx)
{
	int	i;

	i = 0;
	init_mtx(ph, data, 0);
	setup_died(ph, data);
	while (data->n_of_philo > i)
	{
		ph[i].id = i + 1;
		ph[i].start_t = get_time_millsec();
		ph[i].n_of_philo = data->n_of_philo;
		ph[i].last_meal = 0;
		ph[i].full = 0;
		ph[i].t_to_die = data->t_to_die;
		ph[i].t_to_eat = data->t_to_eat;
		ph[i].t_to_sleep = data->t_to_sleep;
		ph[i].n_must_eat = data->n_must_eat;
		pthread_mutex_init(&mtx[i], 0);
		ph[i].r_fork = &mtx[i];
		ph[i].l_fork = &mtx[(i + 1) % data->n_of_philo];
		i++;
	}
}

void	destroy_mtx(t_philo *ph, t_data *data)
{
	int	i;

	i = 0;
	while (data->n_of_philo - 1 > i)
	{
		pthread_mutex_destroy(ph[i].r_fork);
		i++;
	}
	pthread_mutex_destroy(ph[0].died_m);
	pthread_mutex_destroy(ph[0].start);
	pthread_mutex_destroy(ph[0].id_m);
	pthread_mutex_destroy(ph[0].last_meal_m);
	pthread_mutex_destroy(ph[0].full_m);
	pthread_mutex_destroy(ph[0].print);
	free(ph[0].died_m);
	free(ph[0].died);
	free(ph[0].start);
	free(ph[0].id_m);
	free(ph[0].last_meal_m);
	free(ph[0].full_m);
	free(ph[0].print);
}
