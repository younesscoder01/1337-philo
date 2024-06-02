/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:28:17 by ysahraou          #+#    #+#             */
/*   Updated: 2024/06/02 17:06:57 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	ft_ato_num(const char *nptr)
{
	char	*nump;
	long    result;

	nump = (char *)nptr;
	result = 0;
	while (*nump != '\0')
	{
		if (*nump >= '0' && *nump <= '9')
			result = result * 10 + (*nump - 48);
		else
			return -1;
		nump++;
	}
	return (result);
}

int check_args(const char **av)
{
    int i;

    i = 1;
    while (av[i])
    {
        if (ft_ato_num(av[i]) == -1 || ft_ato_num(av[i]) > INT_MAX)
            return (1);
        i++;
    }
    return (0);
}

t_data *set_values(const char **av, int ac)
{
    t_data *d;

    d = malloc(sizeof(t_data));
    d->n_of_philo = ft_ato_num(av[1]);
    d->t_to_die = ft_ato_num(av[2]);
    d->t_to_eat = ft_ato_num(av[3]);
    d->t_to_sleep = ft_ato_num(av[4]);
    if (0 == d->n_of_philo || 0 == d->t_to_die || 0 == d->t_to_eat || 0 == d->t_to_sleep)
        return free(d), NULL;
    if (ac == 6)
        d->n_must_eat = ft_ato_num(av[5]);
    else
        d->n_must_eat = 0;
    return (d);
}
