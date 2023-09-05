/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 00:00:20 by rphuyal           #+#    #+#             */
/*   Updated: 2023/09/05 20:15:29 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

bool	is_game_over(t_host *host)
{
	bool	grab;

	pthread_mutex_lock(&host->key);
	grab = host->game_over;
	pthread_mutex_unlock(&host->key);
	return (grab);
}

void	announcement(t_table *self, char *msg)
{
	uint64_t	diff;

	pthread_mutex_lock(&self->host->key);
	diff = get_current_time() - self->host->start_time;
	if (!self->host->game_over && self->state != EXIT)
		printf("%lu %d %s\n", diff, self->id, msg);
	pthread_mutex_unlock(&self->host->key);
}

void	try_eating(t_table *self, t_table *left, t_table *right, int e_time)
{
	pthread_mutex_lock(&right->lock);
	announcement(self, "has taken a fork");
	pthread_mutex_lock(&left->lock);
	announcement(self, "has taken a fork");
	announcement(self, "is eating");
	pthread_mutex_lock(&self->lock);
	self->state = EATING;
	self->meals++;
	self->last_meal = get_current_time();
	pthread_mutex_unlock(&self->lock);
	sleep_phases(e_time);
	pthread_mutex_unlock(&left->lock);
	pthread_mutex_unlock(&right->lock);
}

void	go_to_bed(t_table *self)
{
	int	s_time;

	pthread_mutex_lock(&self->lock);
	s_time = self->ivals[1];
	announcement(self, "is sleeping");
	self->state = SLEEPING;
	pthread_mutex_unlock(&self->lock);
	sleep_phases(s_time);
}

void	*philo_cycle(void *arg)
{
	t_table			*self;

	self = (t_table *)arg;
	if (self->host->p_count == 1)
		return (single_philo(self));
	if (!(self->id % 2))
		sleep_phases(20);
	while (true)
	{
		if (is_game_over(self->host))
			break ;
		try_eating(self, self->left, self->right, self->ivals[0]);
		if (is_game_over(self->host) || self->state == EXIT)
			break ;
		go_to_bed(self);
		if (is_game_over(self->host))
			break ;
		announcement(self, "is thinking");
	}
	return (NULL);
}
