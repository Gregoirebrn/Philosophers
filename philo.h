/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:52:01 by grebrune          #+#    #+#             */
/*   Updated: 2024/04/09 14:51:00 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

typedef struct s_philo t_philo;

typedef struct s_table
{
	bool			stop;
	long			nbr;
	long			tim_die;
	long			tim_eat;
	long			tim_sleep;
	long			tim_start;
	pthread_t		monitor;
	pthread_mutex_t	m_start;
	pthread_mutex_t	m_table;
	pthread_mutex_t	m_write;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_table;

struct s_philo
{
	long			id;
	long			last_meal;
	bool			full;
	bool			activ;
	pthread_t		thread;
	pthread_mutex_t	*m_fork_first;
	pthread_mutex_t	*m_fork_second;
	t_table			*table;
};

long		get_time(void);
void		ft_usleep(long int time);
void		ft_exit(const char *str);

int			check_philo_alive(t_philo *philo);
int			check_philo_hungry(t_philo *philo);
void		check_write(char *str, t_philo *philo);

void		*monitoring(void *data);

void		init_threads(t_table *table);
void		init_philos(t_table *table);

int			dinner_begin(t_table *table);
void		*thread_activ(void *data);

void		philo_is_thinking(t_philo *philo);

void		ft_clear(t_table *table, int join);

#endif
