/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 02:12:01 by rphuyal           #+#    #+#             */
/*   Updated: 2023/08/08 02:14:04 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	freedom(t_philo *philo)
{
	if (philo->forks)
		free(philo->forks);
	if (philo->threads)
		free(philo->threads);
}
