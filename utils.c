/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ujicama <ujicama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:19:50 by ujicama           #+#    #+#             */
/*   Updated: 2022/07/02 19:34:26 by ujicama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_atoi(const char *str, int *_res)
{
	long long	res;
	int			sign;

	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		res *= 10;
		res += (*str - '0');
		str++;
	}
	if (*str != 0)
		return (1);
	*_res = (res * sign);
	return (0);
}

int	error_exit(t_all *all, int i)
{
	if (i)
		free(all->forks);
	else
	{
		printf ("Error\nInvalid arguments\nUsage:\n./philo ");
		printf ("[number_of_philosophers] [time_to_die] [time_to_eat] ");
		printf ("[time_to_sleep] {number_of_times_each_philosopher_must_eat}\n");
	}
	return (1);
}

int	free_all(t_all *all)
{
	free (all->forks);
	free (all->philos);
	return (0);
}

unsigned long	get_time(void)
{
	struct timeval	tv;
	unsigned long	time;

	gettimeofday(&tv, 0);
	return (time = tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
