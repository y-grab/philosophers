/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ujicama <ujicama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:58:03 by ujicama           #+#    #+#             */
/*   Updated: 2022/05/16 14:37:02 by ujicama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_numeric(char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (argv[j])
	{
		while (argv[j][i])
		{
			if (argv[j][i] < '0' || argv[j][i] > '9'
			|| ft_strlen(argv[j]) > 10)
				return (0);
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_all	all;

	if (!is_numeric(argv))
		return (error_exit(&all, 0));
	if (argc != 5 && argc != 6)
		return (error_exit(&all, 0));
	if (init_arg(&all, argc, argv))
		return (error_exit(&all, 0));
	if (init_forks(&all))
		return (1);
	if (init_philos(&all))
		return (1);
	start_philo_threads(&all);
	return (free_all(&all));
}
