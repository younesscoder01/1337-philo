/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:47:31 by ysahraou          #+#    #+#             */
/*   Updated: 2024/06/01 17:49:47 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
void ft_err_args(int ac)
{
    write(2, "Error\n", 6);
    if (ac >= 6)
        printf("TOO MANY ARGS\n");
    else
        printf("ARGS NOT ENOUGH\n");
}


void ft_err(char *str)
{
    write(2, "Error\n", 6);
    printf("%s\n", str);
}