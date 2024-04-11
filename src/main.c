/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:40:24 by grebrune          #+#    #+#             */
/*   Updated: 2024/04/09 13:47:54 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	ft_atoi(char *nptr)
{
	long	res;
	long	i;

	res = 0;
	i = 0;
	while (nptr[i] == 32 || (nptr[i] > 8 && nptr[i] < 14))
		i++;
	if (nptr[i] == '-' || nptr [i] == '+')
	{
		if (nptr[i] == '-')
			return (write(1, "Only positive number accepted.\n", 31)-1);
		i++;
	}
	while (nptr[i] && nptr[i] > 47 && nptr[i] < 58)
	{
		res = res * 10;
		res = res + nptr[i++] - 48;
	}
	return (res);
}

void	check_tables(char **av, t_table *table)
{
	table->nbr = ft_atoi(av[1]);
	if (table->nbr == -1)
		exit (0);
	table->tim_die = ft_atoi(av[2]);
	if (table->tim_die == -1)
		exit (0);
	table->tim_eat = ft_atoi(av[3]);
	if (table->tim_eat == -1)
		exit (0);
	table->tim_sleep = ft_atoi(av[4]);
	if (table->tim_sleep == -1)
		exit (0);
}

int	main(int ac, char **av)
{
	t_table	table;
	int		i;

	i = -1;
	if (ac < 5 || ac > 6)
		return (write(1, "Error : Wrong number of Arguments.\n", 35), 1);
	check_tables(av, &table);
	init_threads(&table);
	pthread_mutex_lock(&table.m_start);
	while (++i < table.nbr)
	{
		if ( 0 != pthread_create(&table.philos[i].thread, NULL, thread_activ, &table.philos[i]))
			return (check_write("Creation of a thread Crashed.\n", &table.philos[0]), 1);
	}
	pthread_create(&table.monitor, NULL, monitoring, &table);
	pthread_mutex_unlock(&table.m_start);
	return (ft_clear(&table, 1), 0);
}
