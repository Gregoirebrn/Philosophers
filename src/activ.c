/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activ.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:57:00 by grebrune          #+#    #+#             */
/*   Updated: 2024/04/11 17:08:35 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_is_thinking(t_philo *philo)
{
	long	copy_sleep;

	pthread_mutex_lock(&philo->table->m_table);
	copy_sleep = philo->table->tim_sleep;
	if (philo->table->stop == 1)
	{
		pthread_mutex_unlock(&philo->table->m_table);
		return ;
	}
	pthread_mutex_unlock(&philo->table->m_table);
	check_write("is thinking\n", philo);
	ft_usleep(copy_sleep * 1000);
	check_write("is sleeping\n", philo);
	ft_usleep(copy_sleep);
}

void	philo_is_hungry(t_philo *philo)
{
	long	copy_eat;

	pthread_mutex_lock(philo->m_fork_first);
	check_write("has taken a fork\n", philo);
	pthread_mutex_lock(philo->m_fork_second);
	check_write("has taken a fork\n", philo);
	check_write("is eating\n", philo);
	philo->last_meal = get_time();
	copy_eat = philo->table->tim_eat;
	ft_usleep(copy_eat);
	pthread_mutex_unlock(philo->m_fork_second);
	pthread_mutex_unlock(philo->m_fork_first);
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
		usleep(100);
		pthread_mutex_lock(&philo->table->m_table);
	}
	while (philo->activ == true && philo->table->stop != 1) // and not full
	{
		pthread_mutex_unlock(&philo->table->m_table);
		philo_is_hungry(philo);
		philo_is_thinking(philo);
		pthread_mutex_lock(&philo->table->m_table);
	}
	pthread_mutex_unlock(&philo->table->m_table);
	return (NULL);
}
