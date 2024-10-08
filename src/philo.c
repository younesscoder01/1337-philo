/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:16:32 by ysahraou          #+#    #+#             */
/*   Updated: 2024/10/08 16:04:44 by ysahraou         ###   ########.fr       */
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
				printf("%s[%06ld] %i died 💀\n", RED, get_time_millsec()
					- get_start(&philo[i]), get_id(&philo[i]));
				*philo[i].died = 1;
				return (pthread_mutex_unlock(philo->died_m), NULL);
			}
			i++;
		}
		ft_usleep(1);
	}
	return (NULL);
}

void	*routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (philo->n_of_philo == 1)
	{
		print_fork(philo);
		ft_usleep(philo->t_to_die);
		return (NULL);
	}
	if (get_id(philo) % 2 == 0)
		ft_usleep(50);
	while (!check_died(philo) && check_meals(philo))
	{
		get_forks(philo);
		eat(philo);
		put_forks(philo);
		print_sleep(philo);
		pthread_mutex_lock(philo->print);
		if (check_meals(philo) && !check_died(philo))
			printf("%s[%06ld] %i is thinking 💭\n", BLUE, get_time_millsec()
				- get_start(philo), get_id(philo));
		pthread_mutex_unlock(philo->print);
		usleep(500);
	}
	return (NULL);
}

void	thread_create(t_philo *ph, int i, pthread_t checker_t)
{
	i = 0;
	(void)checker_t;
	while (ph[0].n_of_philo > i)
	{
		if (pthread_create(&ph[i].thread, 0, routine, &ph[i]))
			printf("Error\n");
		i++;
	}
}

int	main(int argc, char const *argv[])
{
	t_data		*data;
	t_philo		ph[200];
	t_mt		mtx[200];
	pthread_t	checker_t;
	int			i;

	i = -1;
	checker_t = 0;
	if (argc != 6 && argc != 5)
		return (ft_err_args(argc), 1);
	if (check_args(argv))
		return (ft_err("THE ARGS IS UNCORRECT"), 2);
	data = set_values(argv, argc);
	if (data == NULL)
		return (3);
	init_data(ph, data, mtx);
	thread_create(ph, i, checker_t);
	if (pthread_create(&checker_t, 0, &checker, &ph))
		printf("Error\n");
	pthread_join(checker_t, 0);
	i = 0;
	while (ph[0].n_of_philo > i)
		pthread_join(ph[i++].thread, 0);
	return (destroy_mtx(ph, data), free(data), 0);
}
