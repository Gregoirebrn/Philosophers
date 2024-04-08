/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activ.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:57:00 by grebrune          #+#    #+#             */
/*   Updated: 2024/04/08 15:34:55 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_is_hungry(t_philo *philo)
{
	pthread_mutex_lock(philo->m_fork_first);
	check_write("has taken a first fork!\n", philo);
	pthread_mutex_lock(philo->m_fork_second);
	check_write("has taken a second fork!\n", philo);
	check_write("is eating!\n", philo);
	pthread_mutex_lock(&philo->table->m_table);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->table->m_table);
	ft_usleep(philo->table->tim_eat);
	pthread_mutex_unlock(philo->m_fork_first);
	pthread_mutex_unlock(philo->m_fork_second);
	philo->last_meal = get_time();
}

int	check_philo_alive(t_philo *philo)
{
	long i;

	i = 0;
	while (i < philo->table->nbr)
	{
		pthread_mutex_lock(&philo[i].table->m_table);
		if (philo[i].last_meal > get_time() - philo->table->tim_die)
			return (check_write("A philosopher is dead.\n", philo), 0);
		pthread_mutex_unlock(&philo[i].table->m_table);
		i++;
	}
	return (1);
}

void	*thread_activ(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	ft_usleep(200);
	pthread_mutex_lock(&philo->table->m_table);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->table->m_table);
	pthread_mutex_lock(&philo->table->m_start);
	pthread_mutex_unlock(&philo->table->m_start);
	if (philo->id % 2 == 0)
	{
		check_write("is thinking.\n", philo);
		ft_usleep(100);
	}
	while (philo->table->stop == 1)
	{
		philo_is_hungry(philo);
		philo_is_thinking(philo);
	}
	return (NULL);
}

int	dinner_begin(t_table *table)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&table->m_start);
	while (++i < table->nbr)
	{
		if ( 0 != pthread_create(&table->philos[i].thread, NULL, thread_activ, &table->philos[i]))
			return (check_write("Creation of a thread Crashed.\n", &table->philos[0]), 1);
	}
	pthread_create(&table->monitor, NULL, monitoring, table);
	pthread_mutex_unlock(&table->m_start);
	return (0);
}

