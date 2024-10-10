/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:29:07 by ysahraou          #+#    #+#             */
/*   Updated: 2024/10/08 15:37:31 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	if (check_meals(philo) && !check_died(philo))
	{
		printf("%s[%06ld] %i is sleeping 💤\n", WHITE, get_time_millsec()
			- philo->start_t, get_id(philo));
		pthread_mutex_unlock(philo->print);
		ft_usleep(philo->t_to_sleep);
	}
	else
		pthread_mutex_unlock(philo->print);
}

void	print_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	if (check_meals(philo) && !check_died(philo))
	{
		printf("%s[%06ld] %i has taken a fork 🍴\n", YELLOW, get_time_millsec()
			- philo->start_t, get_id(philo));
	}
	pthread_mutex_unlock(philo->print);
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
	pthread_mutex_lock(philo->r_fork);
	print_fork(philo);
	pthread_mutex_lock(philo->l_fork);
	print_fork(philo);
	pthread_mutex_lock(philo->print);
	if (check_meals(philo) && !check_died(philo))
	{
		printf("%s[%06ld] %i is eating 🥘\n", GREEN, get_time_millsec()
			- get_start(philo), get_id(philo));
		pthread_mutex_unlock(philo->print);
		pthread_mutex_lock(philo->last_meal_m);
		philo->last_meal = get_time_millsec() - get_start(philo);
		pthread_mutex_unlock(philo->last_meal_m);
		pthread_mutex_lock(philo->full_m);
		philo->full++;
		pthread_mutex_unlock(philo->full_m);
		ft_usleep(philo->t_to_eat);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	else
		pthread_mutex_unlock(philo->print);
}
