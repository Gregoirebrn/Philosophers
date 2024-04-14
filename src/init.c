/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:45:33 by grebrune          #+#    #+#             */
/*   Updated: 2024/04/13 14:47:34 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_philos(t_table *table)
{
	int i;

	i = -1;
	while (++i < table->nbr)
	{
		table->philos[i].plate = 0;
		table->philos[i].table = table;
		table->philos[i].id = i + 1;
		table->philos[i].last_meal = get_time(table, 0);
		table->philos[i].m_fork_first = &table->forks[i];
		if (i != table->nbr - 1)
			table->philos[i].m_fork_second = &table->forks[i + 1];
		else
			table->philos[i].m_fork_second = &table->forks[0];
	}
}

void	init_threads(t_table *table)
{
	int	i;

	i = -1;
	table->philos = malloc(sizeof (t_philo) * table->nbr);
	if (!table->philos)
		return (ft_clear(table, 0, 0, 0));
	table->forks = malloc(sizeof (pthread_mutex_t) * table->nbr);
	if (!table->forks)
		return (ft_clear(table, 0, 0, 1));
	if (0 != pthread_mutex_init(&table->m_write, NULL))
		return (ft_clear(table, 0, 0, 2));
	if (0 != pthread_mutex_init(&table->m_table, NULL))
		return (ft_clear(table, 0, 1, 2));
	if (0 != pthread_mutex_init(&table->m_start, NULL))
		return (ft_clear(table, 0, 2 ,2));
	table->stop = 0;
	while (++i < table->nbr)
	{
		if (0 != pthread_mutex_init(&table->forks[i], NULL))
			return (ft_clear(table, 0, i + 10 ,2));
	}
	table->tim_start = get_time(table, 0);
	init_philos(table);
}
