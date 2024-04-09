/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:14:07 by grebrune          #+#    #+#             */
/*   Updated: 2024/04/09 15:32:19 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	check_write(char *str, t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->table->m_write);
	pthread_mutex_lock(&philo->table->m_table);
	time = get_time() - philo->table->tim_start;
	if (str[3] != 'D' && philo->table->stop == 1)
	{
		pthread_mutex_unlock(&philo->table->m_table);
		pthread_mutex_unlock(&philo->table->m_write);
		return ;
	}
	pthread_mutex_unlock(&philo->table->m_table);
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
	pthread_mutex_lock(&table->m_table);
	while (table->stop != 1)
	{
		if (i == table->nbr)
			i = 0;
		if (get_time() - table->philos[i].last_meal >= table->tim_die)
		{
			table->stop = 1;
			table->philos->activ = false;
			pthread_mutex_unlock(&table->m_table);
			check_write("Is DEAD.\n", &table->philos[i]);
			return (NULL);
		}
		pthread_mutex_unlock(&table->m_table);
		ft_usleep(100);
		pthread_mutex_lock(&table->m_table);
		i++;
	}
	return (NULL);
}
