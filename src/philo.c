/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:16:32 by ysahraou          #+#    #+#             */
/*   Updated: 2024/06/02 17:06:34 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void p_datas(t_data *p)
{
    printf("%i\n", p->n_of_philo);
    printf("%i\n", p->t_to_die);
    printf("%i\n", p->t_to_eat);
    printf("%i\n", p->t_to_sleep);
    printf("%i\n", p->n_must_eat);
}

int main(int argc, char const *argv[])
{
    t_data *data;
    

    if (argc != 6 && argc != 5)
        return ft_err_args(argc), 1;
    if (check_args(argv))
        return ft_err("THE ARGS IS UNCORRECT"), 2;
    data = set_values(argv, argc);
    if (data == NULL)
        return ft_err("SOME OF THE ARGS ARE 0"), 3;
    p_datas(data);
    free(data);
    return 0;
}