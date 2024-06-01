/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:16:32 by ysahraou          #+#    #+#             */
/*   Updated: 2024/06/01 17:51:15 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void p_params(t_param *p)
{
    printf("%i\n", p->n_of_philo);
    printf("%i\n", p->t_to_die);
    printf("%i\n", p->t_to_eat);
    printf("%i\n", p->t_to_sleep);
    printf("%i\n", p->n_must_eat);
}

int main(int argc, char const *argv[])
{
    t_param *param;
    

    if (argc != 6 && argc != 5)
        return ft_err_args(argc), 1;
    if (check_args(argv))
        return ft_err("THE ARGS UNCORRECT"), 2;
    param = malloc(sizeof(t_param));
    set_values(argv, param, argc);
    p_params(param);
    free(param);
    return 0;
}