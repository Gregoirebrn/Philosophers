/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:52:24 by grebrune          #+#    #+#             */
/*   Updated: 2024/03/18 17:14:03 by grebrune         ###   ########.fr       */
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

t_arg	check_args(char **av)
{
	t_arg	arg;

	arg.nbr = ft_atoi(av[1]);
	if (arg.nbr == 1)
		exit (0);
	arg.tim_die = ft_atoi(av[2]);
	if (arg.tim_die == 1)
		exit (0);
	arg.tim_eat = ft_atoi(av[3]);
	if (arg.tim_eat == 1)
		exit (0);
	arg.tim_sle = ft_atoi(av[4]);
	if (arg.tim_sle == 1)
		exit (0);
	return (arg);
}

void	check_philo_alive(t_arg arg, t_philo **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i]->tim_die > arg.tim_die)
			ft_exit("A philosopher is dead.\n");
		i++;
	}
}


int	main(int ac, char **av)
{
	t_arg	*arg;
	t_philo	**philo;

	if (ac < 5 || ac > 6)
		return (write(1, "Error : Wrong number of arguments.\n", 35), 1);
	*arg = check_args(&av[1]);
	if (arg == NULL)
		return (write(1, "Error : Wrong of arguments.\n", 35), 1);
	philo = malloc(sizeof (t_philo) * arg->nbr);
	if (init_threads(arg))
		return (write(1, "Shit appends.\n", 35), 1);
}
//check parsing
//thread all philo
//create the forks & give the fork
//protect with mutex the forks