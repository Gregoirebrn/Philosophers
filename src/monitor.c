/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:14:07 by grebrune          #+#    #+#             */
/*   Updated: 2024/04/08 15:34:55 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	check_write(char *str, t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->table->m_write);
	time = get_time() - philo->table->tim_start;
	printf("At %ld philosopher %zu %s", time, philo->id, str);
	pthread_mutex_unlock(&philo->table->m_write);
}

void	*monitoring(void *data)
{
	t_table	*table;
	long	i;

	table = (t_table *)data;
	pthread_mutex_lock(&table->m_start);
	pthread_mutex_unlock(&table->m_start);
	i = 0;
	ft_usleep(100);
	while (table->stop != 1)
	{
		pthread_mutex_lock(&table->m_table);
		if (get_time() - table->philos[i].last_meal >= table->tim_die)
		{
			table->stop = 1;
			check_write("Is taking a tee with Mickeal Jakson.\n", &table->philos[i]);
			pthread_mutex_unlock(&table->m_table);
			return (NULL);
		}
		if (table->stop != 1)
			pthread_mutex_unlock(&table->m_table);
		ft_usleep(100);
		i++;
		if (i == table->nbr)
			i = 0;
	}
	return (NULL);
}

void	philo_is_thinking(t_philo *philo)
{
	check_write("is thinking !\n", philo);
	ft_usleep(philo->table->tim_sleep * 1000);
	check_write("is sleeping !\n", philo);
	ft_usleep(philo->table->tim_sleep);
}