/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:28:17 by ysahraou          #+#    #+#             */
/*   Updated: 2024/06/01 17:47:44 by ysahraou         ###   ########.fr       */
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

void set_values(const char **av, t_param *param, int ac)
{
    param->n_of_philo = ft_ato_num(av[1]);
    param->t_to_die = ft_ato_num(av[2]);
    param->t_to_eat = ft_ato_num(av[3]);
    param->t_to_sleep = ft_ato_num(av[4]);
    if (ac == 6)
        param->n_must_eat = ft_ato_num(av[5]);
    else
        param->n_must_eat = 0;
}