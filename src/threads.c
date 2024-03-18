/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:45:33 by grebrune          #+#    #+#             */
/*   Updated: 2024/03/18 15:53:39 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_threads(t_arg *args)
{
	size_t	i;
	t_list	*lst;

	i = 0;
	while (i < args->nbr)
	{
		ft_lstnew(i , *args);
		if (0 != pthread_create(p1, NULL, check_philo_alive, (void *)arg->tim_die))
			ft_exit("Failed to create a new thread.\n");
		lst = lst->next;
		i++;
	}
}