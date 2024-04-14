/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:52:25 by grebrune          #+#    #+#             */
/*   Updated: 2024/04/12 12:28:41 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long int	get_time(t_table *table, int mutex)
{
	struct	timeval	val;

	if (-1 == gettimeofday(&val, NULL))
	{
		if (mutex == 0)
		{
			check_write("Get time of day crashed.\n", &table->philos[0]);
			pthread_mutex_lock(&table->m_table);
		}
		else
		{
			pthread_mutex_unlock(&table->m_table);
			check_write("Get time of day crashed.\n", &table->philos[0]);
			pthread_mutex_lock(&table->m_table);
		}
		table->stop = 1;
		if (mutex == 0)
			pthread_mutex_unlock(&table->m_table);
		return (0);
	}
	return ((val.tv_sec * 1000) + (val.tv_usec / 1000));
}

void	ft_usleep(long int time, t_table *table, int mutex)
{
	long int	start;

	start = get_time(table, mutex);
	while ((get_time(table, mutex) - start) < time / 1000)
		usleep(150);
}

void	mutex_cleaner(t_table *table, int mutex)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&table->m_write);
	if (mutex >= 2)
		pthread_mutex_destroy(&table->m_table);
	if (mutex >= 3)
		pthread_mutex_destroy(&table->m_start);
	if (mutex > 10)
	{
		while (++i < mutex - 10)
			pthread_mutex_destroy(&table->forks[i]);
	}
}

void	ft_clear(t_table *table, int join, int mutex, int malloc)
{
	int	i;

	i = -1;
	pthread_join(table->monitor, NULL);
	if (join > 0)
	{
		while (++i < join)
			pthread_join(table->philos[i].thread, NULL);
	}
	if (mutex > 0)
		mutex_cleaner(table, mutex);
	if (malloc > 0)
	{
		free(table->philos);
		if (malloc == 2)
			free(table->forks);
	}
	printf("End of simulation.\n");
	exit(0);
}
