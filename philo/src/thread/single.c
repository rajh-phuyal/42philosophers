/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:22:58 by rphuyal           #+#    #+#             */
/*   Updated: 2023/09/12 16:07:44 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	*single_philo(t_table *self)
{
	pthread_mutex_lock(&self->lock);
	pthread_mutex_lock(&self->left->lock);
	printf("%llu %d has taken a fork\n",
		get_current_time() - self->host->start_time, self->id);
	sleep_phases(self->host->to_die);
	printf("\033[91m%llu %d %s\n",
		(get_current_time() - self->host->start_time), self->id, "died");
	pthread_mutex_unlock(&self->left->lock);
	pthread_mutex_unlock(&self->lock);
	return (NULL);
}
