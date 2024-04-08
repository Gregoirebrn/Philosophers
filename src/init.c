/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:45:33 by grebrune          #+#    #+#             */
/*   Updated: 2024/04/08 15:34:55 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_philos(t_table *table)
{
	int i;

	i = -1;
	while (++i < table->nbr)
	{
		table->philos[i].table = table;
		table->philos[i].id = i;
		table->philos[i].full = false;
		table->philos[i].m_fork_first = &table->forks[i].fork;
		if (i != table->nbr - 1)
			table->philos[i].m_fork_second = &table->forks[i + 1].fork;
		else
			table->philos[i].m_fork_second = &table->forks[0].fork;
	}
}

void	init_threads(t_table *table)
{
	int	i;

	i = -1;
	table->philos = malloc(sizeof (t_philo) * table->nbr);
	table->forks = malloc(sizeof (t_fork) * table->nbr);
	pthread_mutex_init(&table->m_write, NULL);
	pthread_mutex_init(&table->m_table, NULL);
	pthread_mutex_init(&table->m_start, NULL);
	table->tim_start = get_time();
	table->stop = 0;
	while (++i < table->nbr)
	{
		if (0 != pthread_mutex_init(&table->forks[i].fork, NULL))
			ft_exit("Failed to create a new thread.\n");
		table->forks[i].fork_id = i;
		i++;
	}
	init_philos(table);
}
