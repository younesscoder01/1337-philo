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

void	get_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_fork(philo);
	pthread_mutex_lock(philo->l_fork);
	print_fork(philo);
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
