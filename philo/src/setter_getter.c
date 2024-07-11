/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter_getter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 18:28:47 by grebrune          #+#    #+#             */
/*   Updated: 2024/07/11 18:31:33 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	find_fork(t_philo *philo, long id)
{
	if (philo->table->nbr == id)
		return (0);
	return (id);
}

int	get_arg(t_table *table, char **av)
{
	table->nbr = ft_atoi(av[1]);
	if (table->nbr <= -1)
		return (1);
	table->tim_die = ft_atoi(av[2]);
	if (table->tim_die <= -1)
		return (1);
	table->tim_eat = ft_atoi(av[3]);
	if (table->tim_eat <= -1)
		return (1);
	table->tim_sleep = ft_atoi(av[4]);
	if (table->tim_sleep <= -1)
		return (1);
	return (0);
}

bool	get_taken(long i, t_philo *philo)
{
	int	bol;

	pthread_mutex_lock(philo->table->philos[i].fork);
	bol = philo->table->philos[i].fork_taken;
	pthread_mutex_unlock(philo->table->philos[i].fork);
	if (bol == 0)
		return (true);
	return (false);
}
