/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ujicama <ujicama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 20:18:50 by ujicama           #+#    #+#             */
/*   Updated: 2022/07/02 20:10:32 by ujicama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_msg(t_all *all, int number, char *str)
{
	pthread_mutex_lock(&all->microphone_m);
	printf("%lu %d %s\n", get_time() - all->start, number, str);
	pthread_mutex_unlock(&all->microphone_m);
}

static int	philo_alive(t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&philo->mutex);
	if ((int)(get_time() - philo->last_eat) > philo->all->time_to_die
		&& philo->eat_c != philo->all->m_eat)
	{
		pthread_mutex_lock(&philo->all->microphone_m);
		printf("%lu %d died\n", get_time() - philo->all->start, philo->p_number);
		i = 0;
		while (i < philo->all->philos_count)
		{
			pthread_mutex_destroy(&philo->all->forks[i].mutex);
			i++;
		}
		pthread_mutex_destroy(&philo->all->microphone_m);
		pthread_mutex_unlock(&philo->mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->mutex);
	return (1);
}

static void	*monitoring(void *data)
{
	t_all	*all;
	int		i;
	int		j;

	all = (t_all *)data;
	j = all->philos_count;
	while (j)
	{
		usleep(500);
		i = 0;
		while (i < all->philos_count)
		{
			if (!(philo_alive(&all->philos[i])))
				return (0);
			pthread_mutex_lock(&all->philos[i].mutex);
			if (all->philos[i].eat_c == all->m_eat && all->philos[i].done)
			{
				j--;
				all->philos[i].done = 0;
			}
			pthread_mutex_unlock(&all->philos[i].mutex);
			i++;
		}
	}
	return (0);
}

void	start_monitoring(t_all *all)
{
	pthread_t	p_id;
	int			i;

	pthread_create(&p_id, 0, monitoring, (void *)all);
	pthread_join(p_id, 0);
	i = 0;
	while (i < all->philos_count)
	{
		pthread_mutex_destroy(&all->philos[i].mutex);
		i++;
	}
}
