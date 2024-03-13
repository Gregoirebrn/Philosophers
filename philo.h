/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:52:01 by grebrune          #+#    #+#             */
/*   Updated: 2024/03/13 18:17:24 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdlib.h>

//number_of_philosophers time_to_die time_to_eat time_to_sleep

typedef struct s_philo
{
	size_t	nbr;
	size_t	tim_die;
	size_t	tim_eat;
	size_t	tim_sle;
}	t_philo;

#endif
