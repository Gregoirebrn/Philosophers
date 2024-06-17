/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activ.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:57:00 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/17 22:57:50 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_is_thinking(t_philo *philo)
{
	check_write("is thinking\n", philo);
	ft_usleep(philo->table->tim_sleep * 1000, philo->table, 0);
	check_write("is sleeping\n", philo);
	ft_usleep(500, philo->table, 0);
}

void	philo_is_hungry(t_philo *philo)
{
	long	copy_eat;

	pthread_mutex_lock(philo->m_fork_first);
	check_write("has taken a fork\n", philo);
	pthread_mutex_lock(philo->m_fork_second);
	check_write("has taken a fork\n", philo);
	check_write("is eating\n", philo);
	philo->last_meal = get_time(philo->table, 0);
	copy_eat = philo->table->tim_eat;
	ft_usleep(copy_eat * 1000, philo->table, 0);
	pthread_mutex_unlock(philo->m_fork_second);
	pthread_mutex_unlock(philo->m_fork_first);
	pthread_mutex_lock(&philo->table->m_table);
	philo->plate += 1;
	pthread_mutex_unlock(&philo->table->m_table);
}

void	*thread_activ(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->table->m_start);
	pthread_mutex_unlock(&philo->table->m_start);
	pthread_mutex_lock(&philo->table->m_table);
	if (philo->id % 2 == 1 && philo->table->stop != 1)
	{
		pthread_mutex_unlock(&philo->table->m_table);
		check_write("is thinking\n", philo);
		ft_usleep(philo->table->tim_sleep * 1000, philo->table, 0);
		pthread_mutex_lock(&philo->table->m_table);
	}
	while (philo->table->stop != 1)
	{
		pthread_mutex_unlock(&philo->table->m_table);
		philo_is_hungry(philo);
		philo_is_thinking(philo);
		pthread_mutex_lock(&philo->table->m_table);
	}
	pthread_mutex_unlock(&philo->table->m_table);
	return (NULL);
}
