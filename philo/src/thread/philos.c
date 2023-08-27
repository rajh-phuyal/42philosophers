/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 00:00:20 by rphuyal           #+#    #+#             */
/*   Updated: 2023/08/27 18:59:37 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	announcement(t_table *self, char *msg)
{
	uint64_t	diff;

	diff = get_current_time() - self->host->start_time;
	pthread_mutex_lock(&self->host->key);
	printf("%llu %d %s\n", diff, self->id, msg);
	pthread_mutex_unlock(&self->host->key);
}

void	try_eating(t_table *self, t_table *left, t_table *right, int e_time)
{
	pthread_mutex_unlock(&self->lock);
	pthread_mutex_lock(&right->lock);
	announcement(self, "has taken a fork");
	pthread_mutex_lock(&left->lock);
	announcement(self, "has taken a fork");
	self->last_meal = get_current_time();
	announcement(self, "is eating");
	self->state = EATING;
	self->meals++;
	sleep_phases(e_time);
	pthread_mutex_unlock(&right->lock);
	pthread_mutex_unlock(&left->lock);
}

void	go_to_bed(t_table *self)
{
	int	s_time;

	announcement(self, "is sleeping");
	pthread_mutex_lock(&self->lock);
	s_time = self->ivals[2];
	self->state = SLEEPING;
	pthread_mutex_unlock(&self->lock);
	sleep_phases(s_time);
}

void	contemplate(t_table *self)
{
	int	c_time;

	announcement(self, "is thinking");
	pthread_mutex_lock(&self->lock);
	c_time = self->ivals[3];
	self->state = THINKING;
	pthread_mutex_unlock(&self->lock);
	sleep_phases(c_time);
}

void	*philo_cycle(void *arg)
{
	t_table			*self;

	self = (t_table *)arg;
	while (true)
	{
		pthread_mutex_lock(&self->lock);
		try_eating(self, self->left, self->right, self->ivals[1]);
		pthread_mutex_lock(&self->lock);
		if (self->state == DEAD)
		{
			announcement(self, "died");
			break ;
		}
		pthread_mutex_unlock(&self->lock);
		go_to_bed(self);
		contemplate(self);
	}
	return (NULL);
}
