/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:16:32 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/21 19:23:50 by ysahraou         ###   ########.fr       */
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

void sleep_m(time_t num)
{
    usleep(num * 1000);
}

time_t get_time_millsec(void)
{
    struct timeval current_time;

    gettimeofday(&current_time, NULL);
    return ((current_time.tv_sec * 1000) +  (current_time.tv_usec / 1000));
}

void *lmaout(void *ph)
{
    int i;
    t_philo *philo;

    philo = (t_philo *)ph;
    while (1)
    {
        i = 0;
        while (philo[0].n_of_philo > i)
        {
            if ((get_time_millsec() - philo->start_t) - philo[i].last_meal >= philo->t_to_die)
            {
                printf("\033[0;31m%ld %i died\n\033[0m", get_time_millsec() - philo->start_t, philo->id);
                *philo[i].died = 1;
                return (NULL);
            }
            i++;
        }
    }
    return (NULL);
}

void print_fork(t_philo *philo)
{
    if (*philo->died == 0)
        printf("\033[0;33m%ld %i has taken a fork\n\033[0m", get_time_millsec() - philo->start_t, philo->id);
}

void *routine(void *ph)
{
    t_philo *philo = (t_philo *)ph;

    while (!*philo->died)
    {
        if (philo->id % 2 == 0)
            usleep(100);
        pthread_mutex_lock(philo->l_fork);
        print_fork(philo);
        pthread_mutex_lock(philo->r_fork);
        print_fork(philo);
    
        if (!*philo->died)
        {
            printf("\033[0;32m%ld %i is eating\n\033[0m", get_time_millsec() - philo->start_t, philo->id);
            sleep_m(philo->t_to_eat);
        }
        philo->last_meal = get_time_millsec() - philo->start_t;
        pthread_mutex_unlock(philo->r_fork);
        pthread_mutex_unlock(philo->l_fork);
        if (!*philo->died)
        {
            printf("\033[0;35m%ld %i is sleeping\n\033[0m", get_time_millsec() - philo->start_t, philo->id);
            sleep_m(philo->t_to_sleep);
        }
        if (!*philo->died)
            printf("\033[0;34m%ld %i  is thinking\n\033[0m", get_time_millsec() - philo->start_t, philo->id);
    }
    return NULL;
}

void    init_data(t_philo *ph, t_data *data)
{
    int i;
    bool *died;

    died = malloc(sizeof(bool));
    *died = 0;
    i = 0;
    while (data->n_of_philo > i)
    {
        ph[i].died = died;
        ph[i].l_fork = malloc(sizeof(pt_mt));
        ph[i].r_fork = malloc(sizeof(pt_mt));
        pthread_mutex_init(ph[i].l_fork, 0);
        i++;
    }
    i = 0;
    while (data->n_of_philo > i)
    {
        ph[i].id = i + 1;
        ph[i].start_t = get_time_millsec();
        ph[i].n_of_philo = data->n_of_philo;
        ph[i].t_to_die = data->t_to_die;
        ph[i].t_to_eat = data->t_to_eat;
        ph[i].t_to_sleep = data->t_to_sleep;
        ph[i].n_must_eat = data->n_must_eat;
        if (i + 1 == data->n_of_philo)
            ph[i].r_fork = ph[0].l_fork;
        else
            ph[i].r_fork = ph[i+1].l_fork;
        i++;
    }
}

int main(int argc, char const *argv[])
{
    t_data *data;
    t_philo ph[200];
    pthread_t lmaout_t;
    int i;
    
    i = 0;
    if (argc != 6 && argc != 5)
        return ft_err_args(argc), 1;
    if (check_args(argv))
        return ft_err("THE ARGS IS UNCORRECT"), 2;
    data = set_values(argv, argc);
    if (data == NULL)
        return ft_err("SOME OF THE ARGS ARE 0"), 3;
    // p_datas(data);
    init_data(ph, data);
    free(data);
    while (ph[0].n_of_philo > i)
    {
        pthread_create(&ph[i].thread, 0, routine, &ph[i]);
        i++;
    }
    pthread_create(&lmaout_t, 0, &lmaout, ph);
    pthread_join(lmaout_t, 0);
    i = 0;
    while (ph[0].n_of_philo > i)
    {
        pthread_join(ph[i].thread, 0);
        i++;
    }
    i = 0;
    while (ph[0].n_of_philo > i)
    {
        pthread_mutex_destroy(ph[i].l_fork);
        i++;
    }
    return 0;
}
