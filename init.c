/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ujicama <ujicama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:31:00 by ujicama           #+#    #+#             */
/*   Updated: 2022/05/16 14:29:30 by ujicama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_forks(t_all *all)
{
	t_fork	*forks;
	int		i;

	forks = (t_fork *)malloc(sizeof(t_fork) * all->philos_count);
	if (!forks)
		return (1);
	i = 0;
	while (i < all->philos_count)
	{
		forks[i].f_number = i + 1;
		if (pthread_mutex_init(&forks[i].mutex, 0))
		{
			free (forks);
			return (1);
		}
		i++;
	}
	all->forks = forks;
	return (0);
}

int	init_philos(t_all *all)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)malloc(sizeof(t_philo) * all->philos_count);
	if (!philos)
		return (error_exit(all, 1));
	i = 0;
	while (i < all->philos_count)
	{
		philos[i].p_number = i + 1;
		philos[i].eat_c = 0;
		philos[i].done = 1;
		philos[i].left_f = &all->forks[i];
		philos[i].right_f = &all->forks[(i + 1) % all->philos_count];
		pthread_mutex_init(&philos[i].mutex, 0);
		i++;
	}
	all->philos = philos;
	return (0);
}

int	init_arg(t_all *all, int argc, char **argv)
{
	if (ft_atoi(argv[1], &all->philos_count))
		return (error_exit(all, 0));
	if (ft_atoi(argv[2], &all->time_to_die))
		return (error_exit(all, 0));
	if (ft_atoi(argv[3], &all->time_to_eat))
		return (error_exit(all, 0));
	if (ft_atoi(argv[4], &all->time_to_sleep))
		return (error_exit(all, 0));
	if (argc == 5)
		all->m_eat = -1;
	else if (argc == 6 && ft_atoi(argv[5], &all->m_eat))
		return (error_exit(all, 0));
	if (all->philos_count < 1 || all->time_to_eat < 10
		|| all->time_to_sleep < 10 || all->time_to_die < 10
		|| (all->m_eat < 1 && argc == 6))
		return (1);
	return (0);
}
