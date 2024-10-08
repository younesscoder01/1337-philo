/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rsrc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:27:21 by ysahraou          #+#    #+#             */
/*   Updated: 2024/10/08 12:40:16 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

time_t	get_time_millsec(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

time_t	get_start(t_philo *philo)
{
	time_t	ret;

	pthread_mutex_lock(philo->start);
	ret = philo->start_t;
	pthread_mutex_unlock(philo->start);
	return (ret);
}

void	ft_usleep(time_t time)
{
	time_t	start;

	start = get_time_millsec();
	if (time - 10 > 0)
		usleep((time - 10) * 1000);
	while (get_time_millsec() - start < time)
		usleep(100);
}

int	get_id(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(philo->id_m);
	ret = philo->id;
	pthread_mutex_unlock(philo->id_m);
	return (ret);
}

time_t	get_last_meal(t_philo *philo)
{
	time_t	ret;

	pthread_mutex_lock(philo->last_meal_m);
	ret = philo->last_meal;
	pthread_mutex_unlock(philo->last_meal_m);
	return (ret);
}
