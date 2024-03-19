/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:45:33 by grebrune          #+#    #+#             */
/*   Updated: 2024/03/19 14:05:15 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	basic_threads(t_arg *arg)
{
	pthread_mutex_init(&arg->m_write, NULL);
	pthread_mutex_init(&arg->m_eat, NULL);
	pthread_mutex_init(&arg->m_dead, NULL);
}

int	init_threads(t_arg *args)
{
	size_t	i;
	t_philo	**tab;

	i = 0;
	tab = malloc(sizeof (t_philo) * args->nbr);
	while (i < args->nbr)
	{
		make_tab(i, *args);
		if (0 != pthread_create(tab[i]->thread, NULL, check_philo_alive, (void *)args->tim_die))
			ft_exit("Failed to create a new thread.\n");
		i++;
	}
}