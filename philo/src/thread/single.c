/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:22:58 by rphuyal           #+#    #+#             */
/*   Updated: 2023/09/12 19:50:29 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	*single_philo(t_table *self)
{
	pthread_mutex_lock(&self->lock);
	pthread_mutex_lock(&self->left->lock);
	printf("\033[97m%lu %d has taken a fork\n\033[0m",
		get_current_time() - self->host->start_time, self->id);
	sleep_phases(self->host->to_die);
	printf("\033[91m%lu %d %s\n\033[0m",
		(get_current_time() - self->host->start_time), self->id, "died");
	pthread_mutex_unlock(&self->left->lock);
	pthread_mutex_unlock(&self->lock);
	return (NULL);
}
