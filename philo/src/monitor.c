/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:14:07 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/18 15:33:13 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	check_write(char *str, t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->table->m_write);
	pthread_mutex_lock(&philo->table->m_table);
	time = get_time(philo->table, 1) - philo->table->tim_start;
	if ((str[0] == 'd' || str [0] == 'A') && philo->table->stop == 1)
	{
		printf("\033[0;31m%ld %zu %s\033[0m", time, philo->id, str);
		pthread_mutex_unlock(&philo->table->m_table);
		pthread_mutex_unlock(&philo->table->m_write);
		return ;
	}
	if (philo->table->stop == 1)
	{
		pthread_mutex_unlock(&philo->table->m_table);
		pthread_mutex_unlock(&philo->table->m_write);
		return ;
	}
	printf("%ld %zu %s", time, philo->id, str);
	pthread_mutex_unlock(&philo->table->m_table);
	pthread_mutex_unlock(&philo->table->m_write);
}

int	check_full(t_table *table)
{
	long	i;
	long	time_to_eat;

	i = -1;
	time_to_eat = 0;
	if (table->plates == 0)
		return (0);
	while (++i < table->nbr)
	{
		if (table->philos[i].plate >= table->plates)
			time_to_eat += 1;
	}
	if (time_to_eat == table->nbr)
	{
		table->stop = 1;
		return (1);
	}
	return (0);
}

int	monitoring_loop(t_table *table, long i)
{
	while (table->stop != 1)
	{
		if (i == table->nbr)
			i = 0;
		if (get_time(table, 1) - table->philos[i].last_meal >= table->tim_die)
		{
			table->stop = 1;
			pthread_mutex_unlock(&table->m_table);
			check_write("died\n", &table->philos[i]);
			return (1);
		}
		if (1 == check_full(table))
		{
			pthread_mutex_unlock(&table->m_table);
			check_write("All philosophers are full.\n", &table->philos[i]);
			return (1);
		}
		else
			pthread_mutex_unlock(&table->m_table);
		ft_usleep(100, table, 0);
		pthread_mutex_lock(&table->m_table);
		i++;
	}
	return (0);
}

void	*monitoring(void *data)
{
	t_table	*table;
	long	i;

	table = (t_table *)data;
	pthread_mutex_lock(&table->m_start);
	pthread_mutex_unlock(&table->m_start);
	ft_usleep(table->tim_die * 1000, table, 0);
	pthread_mutex_lock(&table->m_table);
	i = 0;
	if (monitoring_loop(table, i))
		return (0);
	pthread_mutex_unlock(&table->m_table);
	return (NULL);
}
