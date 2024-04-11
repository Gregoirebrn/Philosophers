/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:52:25 by grebrune          #+#    #+#             */
/*   Updated: 2024/04/11 15:15:55 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_exit(const char *str)
{
	printf("%s", str);
}

long int	get_time(void)
{
	struct	timeval	val;

	if (-1 == gettimeofday(&val, NULL))
		ft_exit("Gettimeofday crashed.\n");
	return ((val.tv_sec * 1000) + (val.tv_usec / 1000));
}

void	ft_usleep(long int time)
{
	long int	start;

	start = get_time();
	while ((get_time() - start) < time / 1000)
		usleep(150);
}

void	mutex_cleaner(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nbr)
		pthread_mutex_destroy(&table->forks[i]);
	pthread_mutex_destroy(&table->m_table);
	pthread_mutex_destroy(&table->m_start);
	pthread_mutex_destroy(&table->m_write);
}

void	ft_clear(t_table *table, int join)
{
	int	i;

	i = 0;
	if (join == 1)
	{
		pthread_join(table->monitor, NULL);
		while (i < table->nbr)
		{
			pthread_join(table->philos[i].thread, NULL);
			i++;
		}
	}
	free(table->forks);
	free(table->philos);
	printf("End of simulation.\n");
	exit(0);
}
