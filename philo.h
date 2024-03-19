/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:52:01 by grebrune          #+#    #+#             */
/*   Updated: 2024/03/19 14:05:38 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
// compilation -lpthread
//number_of_philosophers time_to_die time_to_eat time_to_sleep

typedef struct s_arg
{
	size_t			nbr;
	size_t			tim_die;
	size_t			tim_eat;
	size_t			tim_sle;
	int				stop;
	pthread_mutex_t	m_write;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	m_eat;
}	t_arg;

typedef struct s_philo
{
	size_t			name;
	size_t			tim_die;
	size_t			tim_eat;
	size_t			tim_sle;
	pthread_t		*thread;
	int				stop;
	pthread_mutex_t	mutex;
	int				fork;
}	t_philo;

long int	get_time(void);
void		ft_usleep(long int time);
void		ft_exit(const char *str);

void		check_philo_alive(t_arg arg, t_philo **tab);
void		check_philo_hungry(t_arg arg, t_philo **tab);
t_philo		*make_tab(size_t i, t_arg file);
int			init_threads(t_arg *args);

#endif
