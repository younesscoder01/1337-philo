/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:29:07 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/26 09:53:09 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_sleep(t_philo *philo)
{
	if (!check_died(philo) && check_meals(philo))
	{
		printf("\033[0;36m%ld %i is sleeping\n\033[0m", get_time_millsec()
			- philo->start_t, get_id(philo));
		sleep_m(philo->t_to_sleep);
	}
}

void	print_fork(t_philo *philo)
{
	if (!check_died(philo) && check_meals(philo))
		printf("\033[0;33m%ld %i has taken a fork\n\033[0m", get_time_millsec()
			- philo->start_t, get_id(philo));
}

int	check_died(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(philo->died_m);
	ret = *philo->died;
	pthread_mutex_unlock(philo->died_m);
	return (ret);
}

int	check_meals(t_philo *philo)
{
	bool	ret;

	ret = 1;
	if (philo->n_must_eat > 0)
	{
		pthread_mutex_lock(philo->full_m);
		ret = !(philo->n_must_eat == philo->full);
		pthread_mutex_unlock(philo->full_m);
	}
	return (ret);
}

void	eat(t_philo *philo)
{
	if (!check_died(philo) && check_meals(philo))
	{
		printf("\033[0;32m%ld %i is eating\n\033[0m", get_time_millsec()
			- get_start(philo), get_id(philo));
		pthread_mutex_lock(philo->last_meal_m);
		philo->last_meal = get_time_millsec() - get_start(philo);
		pthread_mutex_unlock(philo->last_meal_m);
		pthread_mutex_lock(philo->full_m);
		philo->full++;
		pthread_mutex_unlock(philo->full_m);
		sleep_m(philo->t_to_eat);
	}
}