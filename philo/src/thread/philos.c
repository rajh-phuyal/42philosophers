/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 00:00:20 by rphuyal           #+#    #+#             */
/*   Updated: 2023/09/04 18:48:51 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	announcement(t_table *self, char *msg)
{
	uint64_t	diff;

	pthread_mutex_lock(&self->host->key);
	pthread_mutex_lock(&self->lock);
	diff = get_current_time() - self->host->start_time;
	if (self->state != DEAD && self->state != EXIT)
		printf("%llu %d %s\n", diff, self->id, msg);
	pthread_mutex_unlock(&self->host->key);
	pthread_mutex_unlock(&self->lock);
}

void	try_eating(t_table *self, t_table *left, t_table *right, int e_time)
{
	pthread_mutex_unlock(&self->lock);
	pthread_mutex_lock(&right->lock);
	announcement(self, "has taken a fork");
	pthread_mutex_lock(&left->lock);
	announcement(self, "has taken a fork");
	announcement(self, "is eating");
	pthread_mutex_lock(&self->lock);
	self->state = EATING;
	self->meals++;
	self->last_meal = get_current_time();
	sleep_phases(e_time);
	pthread_mutex_unlock(&self->lock);
	pthread_mutex_unlock(&right->lock);
	pthread_mutex_unlock(&left->lock);
}

void	go_to_bed(t_table *self)
{
	int	s_time;

	announcement(self, "is sleeping");
	pthread_mutex_lock(&self->lock);
	s_time = self->ivals[1];
	self->state = SLEEPING;
	pthread_mutex_unlock(&self->lock);
	sleep_phases(s_time);
}

void	single_philo(t_table *self)
{
	pthread_mutex_lock(&self->lock);
	pthread_mutex_lock(&self->left->lock);
	printf("%llu %d has taken a fork\n",
		get_current_time() - self->host->start_time, self->id);
	sleep_phases(self->host->to_die);
	printf("%llu %d %s\n",
		(get_current_time() - self->host->start_time), self->id, "died");
	pthread_mutex_unlock(&self->left->lock);
	pthread_mutex_unlock(&self->lock);
	return ;
}

void	*philo_cycle(void *arg)
{
	t_table			*self;

	self = (t_table *)arg;
	if (self->host->p_count == 1)
	{
		single_philo(self);
		return (NULL);
	}
	if (!(self->id % 2))
		sleep_phases(20);
	while (true)
	{
		pthread_mutex_lock(&self->lock);
		if (self->state == DEAD || self->state == EXIT)
			return (NULL);
		try_eating(self, self->left, self->right, self->ivals[0]);
		go_to_bed(self);
		announcement(self, "is thinking");
		printf("stuck in check_node_status\n");
	}
	return (NULL);
}
