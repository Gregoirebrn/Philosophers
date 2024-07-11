/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:40:24 by grebrune          #+#    #+#             */
/*   Updated: 2024/07/11 16:35:05 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] > 47 && str[i] < 58))
			return (1);
		i++;
	}
	return (0);
}

long	ft_atoi(char *str)
{
	long	res;
	long	i;

	res = 0;
	i = 0;
	if (check_num(str) == 1)
		return (printf("A number is with digit not anything else.\n"), -1);
	while (str[i] && str[i] > 47 && str[i] < 58)
	{
		res = res * 10;
		res = res + str[i++] - 48;
	}
	return (res);
}

int	check_tables(char **av, t_table *table, int ac)
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
	if (ac == 6)
	{
		table->plates = ft_atoi(av[5]);
		if (table->plates == -1)
			return (printf("Wrong number of times to eat.\n"), 1);
		if (table->plates == 0)
			return (printf("All philosophers are full.\n"), 1);
	}
	else
		table->plates = 0;
	if (table->nbr <= 0)
		return (write(2, "Where the philosophers at ?\n", 28), 1);
	if (table->tim_sleep < 60 || table->tim_eat < 60 || table->tim_die < 60)
		return (write(2, "Numbers to low, results would be undefined.\n", 44), 1);
	return (0);
}

void	*solobolo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->table->m_start);
	pthread_mutex_unlock(&philo->table->m_start);
	pthread_mutex_lock(philo->fork);
	check_write("has taken a fork\n", philo);
	pthread_mutex_unlock(philo->fork);
	ft_usleep(philo->table->tim_die * 1000, philo->table, 0);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_table	table;
	int		i;

	i = -1;
	if (ac < 5 || ac > 6)
		return (write(1, "Error : Wrong number of Arguments.\n", 35), 1);
	if (1 == check_tables(av, &table, ac))
		return (1);
	init_threads(&table);
	pthread_mutex_lock(&table.m_start);
	if (start_threads(table, i))
		return (1);
	pthread_create(&table.monitor, NULL, monitoring, &table);
	pthread_mutex_unlock(&table.m_start);
	return (ft_clear(&table, (int)table.nbr, (int)table.nbr + 10, 2), 0);
}
