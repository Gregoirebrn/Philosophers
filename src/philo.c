/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:52:24 by grebrune          #+#    #+#             */
/*   Updated: 2024/03/13 18:17:24 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

size_t	ft_atoi(const char *nptr)
{
	size_t	res;
	size_t	signe;
	size_t	i;

	signe = 1;
	res = 0;
	i = 0;
	while (nptr[i] == 32 || (nptr[i] > 8 && nptr[i] < 14))
		i++;
	if (i > 0)
		return (1);
	if (nptr[i] == '-' || nptr [i] == '+')
	{
		if (nptr[i] == '-')
			return (1);
		i++;
	}
	while (nptr[i] > 47 && nptr[i] < 58)
	{
		res = res * 10;
		res = res + nptr[i++] - 48;
	}
	return (res * signe);
}

t_philo	check_args(char **av)
{
	t_philo	philo;

	philo.nbr = ft_atoi(av[1]);
	if (philo.nbr == 1)
		exit (0);
	philo.tim_die = ft_atoi(av[2]);
	if (philo.tim_die == 1)
		exit (0);
	philo.tim_eat = ft_atoi(av[3]);
	if (philo.tim_eat == 1)
		exit (0);
	philo.tim_sle = ft_atoi(av[4]);
	if (philo.tim_sle == 1)
		exit (0);
	return (philo);
}
//number_of_philosophers time_to_die time_to_eat time_to_sleep
int	main(int ac, char **av)
{
	t_philo	philo;

	if (ac < 5 || ac > 6)
		return (write(1, "Error : Wrong number of arguments.\n", 35), 1);
	philo = check_args(&av[1])
		(write(1, "Error : Wrong value of arguments.\n", 35), 1);
}