/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ujicama <ujicama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:12:32 by ujicama           #+#    #+#             */
/*   Updated: 2022/07/02 20:10:28 by ujicama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(unsigned long argv)
{
	long	time;

	time = get_time();
	while (argv > get_time() - time)
		usleep(500);
}

static void	take_forks(t_philo *philo)
{
	if (philo->left_f->f_number < philo->right_f->f_number)
	{
		pthread_mutex_lock(&philo->left_f->mutex);
		print_msg(philo->all, philo->p_number, "has taken a fork");
		pthread_mutex_lock(&philo->right_f->mutex);
		print_msg(philo->all, philo->p_number, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->right_f->mutex);
		print_msg(philo->all, philo->p_number, "has taken a fork");
		pthread_mutex_lock(&philo->left_f->mutex);
		print_msg(philo->all, philo->p_number, "has taken a fork");
	}
}

static void	eat(t_philo *philo)
{
	take_forks(philo);
	print_msg(philo->all, philo->p_number, "is eating");
	pthread_mutex_lock(&philo->mutex);
	philo->last_eat = get_time();
	philo->eat_c++;
	pthread_mutex_unlock(&philo->mutex);
	ft_usleep (philo->all->time_to_eat);
	pthread_mutex_unlock(&philo->right_f->mutex);
	pthread_mutex_unlock(&philo->left_f->mutex);
}

static void	*routine(void *data)
{
	t_philo		*philo;
	int			i;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->mutex);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->mutex);
	i = 0;
	while (i != philo->all->m_eat)
	{
		eat(philo);
		print_msg(philo->all, philo->p_number, "is sleeping");
		pthread_mutex_lock(&philo->mutex);
		ft_usleep(philo->all->time_to_sleep);
		pthread_mutex_unlock(&philo->mutex);
		print_msg(philo->all, philo->p_number, "is thinking");
		i++;
	}
	return (0);
}

void	start_philo_threads(t_all *all)
{
	int			i;

	i = 0;
	all->start = get_time();
	pthread_mutex_init(&all->microphone_m, 0);
	while (i < all->philos_count)
	{
		usleep(1);
		all->philos[i].all = all;
		pthread_create(&all->philos[i].t_id, 0, \
		routine, (void *)&all->philos[i]);
		pthread_detach(all->philos[i].t_id);
		i++;
	}
	start_monitoring(all);
}
