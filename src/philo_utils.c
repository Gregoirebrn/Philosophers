/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:52:25 by grebrune          #+#    #+#             */
/*   Updated: 2024/03/18 13:30:34 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_exit(const char *str)
{
	printf(str);
	exit;
}

long int	get_time(void)
{
	struct	timeval	*val;

	val = NULL;
	if (-1 == gettimeofday(val, NULL))
		ft_exit("Gettimeofday crashed.\n");
	return ((val->tv_sec * 1000) + (val->tv_usec / 1000));
}

void	ft_usleep(long int time)
{
	long int	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(time / 10);
}