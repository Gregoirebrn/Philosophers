/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:52:01 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/30 16:31:12 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_philo	t_philo;

typedef struct s_table
{
	bool			stop;
	long			nbr;
	long			tim_die;
	long			tim_eat;
	long			tim_sleep;
	long			tim_start;
	long			plates;
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
	pthread_mutex_t	m_last;
	long			plate;
	pthread_t		thread;
	pthread_mutex_t	*fork;
	int				fork_taken;
	t_table			*table;
};

//activ
void	philo_is_thinking(t_philo *philo);
void	philo_is_hungry(t_philo *philo);
void	*thread_activ(void *data);
//init
void	init_threads(t_table *table);
void	init_philos(t_table *table, int mutex);
int		start_threads(t_table table, int i);
//main
int		check_num(char *str);
long	ft_atoi(char *str);
int		check_tables(char **av, t_table *table, int ac);
void	*solobolo(void *data);
//monitor
void	check_write(char *str, t_philo *philo);
int		check_full(t_table *table);
int		monitoring_loop(t_table *table, long i);
void	*monitoring(void *data);
//time_clear
void	ft_usleep(long int time, t_table *table, int mutex);
long	get_time(t_table *table, int mutex);
void	mutex_cleaner(t_table *table, int mutex);
void	ft_clear(t_table *table, int join, int mutex, int malloc);

#endif
