/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:16:32 by ysahraou          #+#    #+#             */
/*   Updated: 2024/10/07 18:18:06 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_usleep(time_t time)
{
	time_t	start;

	start = get_time_millsec();
	if (time - 10 > 0)
		usleep(time - 10);
	while (get_time_millsec() - start < time - 10)
		usleep(100);
}

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
				pthread_mutex_unlock(philo->died_m);
				return (NULL);
			}
			i++;
		}
		ft_usleep(1);
	}
	return (NULL);
}

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

void	*routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (philo->n_of_philo == 1)
	{
		pthread_mutex_lock(philo->print);
		printf("%s[%06ld] %i has taken a fork 🍴\n", YELLOW, get_time_millsec()
			- philo->start_t, get_id(philo));
		pthread_mutex_unlock(philo->print);
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
		if (!check_died(philo) && check_meals(philo))
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
	while (ph[0].n_of_philo > i)
	{
		if (pthread_create(&ph[i].thread, 0, routine, &ph[i]))
			printf("Error\n");
		i++;
	}
	if (pthread_create(&checker_t, 0, &checker, &ph))
		printf("Error\n");
}

void	allocat(t_philo **ph, t_data *data, t_mt **mtx)
{
	int	i;

	i = 0;
	*ph = malloc(sizeof(t_philo) * data->n_of_philo);
	*mtx = malloc(sizeof(t_mt) * data->n_of_philo);
}

int	main(int argc, char const *argv[])
{
	t_data		*data;
	t_philo		*ph;
	t_mt		*mtx;
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
		return (ft_err("SOME OF THE ARGS ARE 0"), 3);
	allocat(&ph, data, &mtx);
	init_data(ph, data, mtx);
	thread_create(ph, i, checker_t);
	pthread_join(checker_t, 0);
	i = 0;
	while (ph[0].n_of_philo > i)
		pthread_join(ph[i++].thread, 0);
	destroy_mtx(ph, data, mtx);
	free(data);
	return (0);
}
