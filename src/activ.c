/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activ.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:57:00 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/30 18:07:32 by grebrune         ###   ########.fr       */
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

long	find_fork(t_philo *philo, long id)
{
	if (philo->table->nbr == id)
		return (0);
	return (id);
}

void	wait_or_take(long i, t_philo *philo, int unlock)
{
	if (unlock)
	{
		pthread_mutex_lock(philo->table->philos[i].fork);
		philo->table->philos[i].fork_taken = 0;
		pthread_mutex_unlock(philo->table->philos[i].fork);
		return ;
	}
	while (42)
	{
		if (philo->table->philos[i].fork_taken == 0)
		{
			pthread_mutex_lock(philo->table->philos[i].fork);
			philo->table->philos[i].fork_taken = 1;
			pthread_mutex_unlock(philo->table->philos[i].fork);
			return ;
		}
	}
}

void	philo_is_hungry(t_philo *philo)
{
	long	copy_eat;
	long	i;

	i = find_fork(philo, philo->id);
	wait_or_take(philo->id - 1, philo, 0);
	check_write("has taken a fork\n", philo);
	wait_or_take(i, philo, 0);
	check_write("has taken a fork\n", philo);
	check_write("is eating\n", philo);
	philo->last_meal = get_time(philo->table, 0);
	copy_eat = philo->table->tim_eat;
	ft_usleep(copy_eat * 1000, philo->table, 0);
	wait_or_take(philo->id - 1, philo, 1);
	wait_or_take(i, philo, 1);
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
	if (philo->id % 2 == 0 && philo->table->stop != 1)
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
