/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 00:00:20 by rphuyal           #+#    #+#             */
/*   Updated: 2023/08/26 14:17:27 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	announcement(t_table *self, char *msg)
{
	pthread_mutex_lock(self->key);
	printf("%d %d %s\n", gettimeofday(&self->time, NULL) * 1000, self->id, msg);
	pthread_mutex_unlock(self->key);
}

void	*philo_cycle(void *arg)
{
	unsigned long	time;
	t_table			*self;

	self = (t_table *)arg;
	while (true)
	{
		pthread_mutex_lock(&self->lock);
		announcement(self, "is sleeping");
		self->state = SLEEPING;
		time = self->ivals[0];
		pthread_mutex_unlock(&self->lock);
		usleep(time);
		pthread_mutex_lock(&self->lock);
		announcement(self, "died");
		self->state = DEAD;
		pthread_mutex_unlock(&self->lock);
		if (self->state == DEAD)
			break ;
		pthread_mutex_lock(&self->lock);
		announcement(self, "is eating");
		self->meals++;
		self->state = EATING;
		time = self->ivals[1];
		pthread_mutex_unlock(&self->lock);
		usleep(time);
	}
	return (NULL);
}
