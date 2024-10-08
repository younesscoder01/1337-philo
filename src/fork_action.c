/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:37:50 by ysahraou          #+#    #+#             */
/*   Updated: 2024/10/08 09:41:18 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	left_right(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_fork(philo);
	pthread_mutex_lock(philo->r_fork);
	print_fork(philo);
}

void	right_left(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_fork(philo);
	pthread_mutex_lock(philo->l_fork);
	print_fork(philo);
}

void	get_forks(t_philo *philo)
{
	if (philo->r_fork > philo->l_fork)
		left_right(philo);
	else
		right_left(philo);
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
