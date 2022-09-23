/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ujicama <ujicama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:58:48 by ujicama           #+#    #+#             */
/*   Updated: 2022/05/16 14:31:16 by ujicama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h> 
# include <pthread.h>
# include <sys/time.h>

typedef struct s_all	t_all;

typedef struct s_fork
{
	int				f_number;
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_philo
{
	int				p_number;
	int				eat_c;
	unsigned long	last_eat;
	int				done;
	t_fork			*left_f;
	t_fork			*right_f;
	t_all			*all;
	pthread_t		t_id;
	pthread_mutex_t	mutex;
}					t_philo;

typedef struct s_all
{
	int				philos_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				m_eat;
	unsigned long	start;
	t_philo			*philos;
	t_fork			*forks;
	pthread_mutex_t	microphone_m;
}					t_all;

int					ft_strlen(const char *s);
int					error_exit(t_all *all, int i);
int					free_all(t_all *all);
int					ft_atoi(const char *str, int *_res);
int					init_forks(t_all *all);
int					init_philos(t_all *all);
int					init_arg(t_all *all, int argc, char **argv);
unsigned long		get_time(void);
void				ft_usleep(unsigned long argv);
void				start_philo_threads(t_all *all);
void				print_msg(t_all *all, int number, char *str);
void				start_monitoring(t_all *all);

#endif