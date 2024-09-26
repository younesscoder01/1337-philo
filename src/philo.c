/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:16:32 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/26 09:50:00 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_full(t_philo *philo)
{
	int	j;

	j = 0;
	while (philo[0].n_of_philo > j && !check_meals(&philo[j]))
		j++;
	if (philo[0].n_of_philo == j)
		return (0);
	return (1);
}

void	*checker(void *ph)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)ph;
	while (1)
	{
		i = 0;
		while (philo[0].n_of_philo > i)
		{
			if (!check_full(philo))
				return (NULL);
			if ((get_time_millsec() - get_start(&philo[i]))
				- get_last_meal(&philo[i]) >= philo->t_to_die)
			{
				pthread_mutex_lock(philo->died_m);
				printf("\033[0;31m%ld %i died\n\033[0m", get_time_millsec()
					- get_start(&philo[i]), get_id(&philo[i]));
				*philo[i].died = 1;
				pthread_mutex_unlock(philo->died_m);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

void	get_forks(t_philo *philo)
{
	if (get_id(philo) % 2 != 0)
		usleep(1000);
	if (get_id(philo) % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		print_fork(philo);
		pthread_mutex_lock(philo->r_fork);
		print_fork(philo);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_fork(philo);
		pthread_mutex_lock(philo->l_fork);
		print_fork(philo);
	}
}

void	*routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	while (!check_died(philo) && check_meals(philo))
	{
		if (philo->n_of_philo == 1)
		{
			printf("\033[0;33m%ld %i has taken a fork\n\033[0m",
				get_time_millsec() - philo->start_t, get_id(philo));
			sleep_m(philo->t_to_die);
			break ;
		}
		get_forks(philo);
		eat(philo);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		print_sleep(philo);
		if (!check_died(philo) && check_meals(philo))
			printf("\033[0;34m%ld %i  is thinking\n\033[0m", get_time_millsec()
				- get_start(philo), get_id(philo));
	}
	return (NULL);
}

int	main(int argc, char const *argv[])
{
	t_data		*data;
	t_philo		ph[200];
	pthread_t	checker_t;
	int			i;

	i = -1;
	if (argc != 6 && argc != 5)
		return (ft_err_args(argc), 1);
	if (check_args(argv))
		return (ft_err("THE ARGS IS UNCORRECT"), 2);
	data = set_values(argv, argc);
	if (data == NULL)
		return (ft_err("SOME OF THE ARGS ARE 0"), 3);
	init_data(ph, data);
	while (ph[0].n_of_philo > ++i)
		pthread_create(&ph[i].thread, 0, routine, &ph[i]);
	pthread_create(&checker_t, 0, &checker, &ph);
	pthread_join(checker_t, 0);
	i = 0;
	while (ph[0].n_of_philo > i)
		pthread_join(ph[i++].thread, 0);
	destroy_mtx(ph, data);
	free(data);
	return (0);
}
