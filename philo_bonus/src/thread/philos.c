/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 00:00:20 by rphuyal           #+#    #+#             */
/*   Updated: 2023/09/09 03:19:08 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

bool	is_game_over(t_host *host)
{
	bool	state;

	pthread_mutex_lock(&host->key);
	state = host->game_over;
	pthread_mutex_unlock(&host->key);
	return (state);
}

void	announcement(t_table *self, char *msg, char *color)
{
	uint64_t	diff;

	pthread_mutex_lock(&self->host->key);
	diff = get_current_time() - self->host->start_time;
	if (!self->host->game_over && self->state != EXIT)
		printf("%s%llu %d %s\n\033[0m", color, diff, self->id, msg);
	pthread_mutex_unlock(&self->host->key);
}

void	try_eating(t_table *self, t_table *left, t_table *right, int e_time)
{
	if (self->id % 2)
	{
		pthread_mutex_lock(&right->lock);
		announcement(self, "has taken a right fork", "");
		pthread_mutex_lock(&left->lock);
		announcement(self, "has taken a left fork", "");
	}
	else
	{
		pthread_mutex_lock(&left->lock);
		announcement(self, "has taken a left fork", "");
		pthread_mutex_lock(&right->lock);
		announcement(self, "has taken a right fork", "");
	}
	announcement(self, "is eating", "\033[92m");
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
	announcement(self, "is sleeping", "\033[94m");
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
	while (true)
	{
		if (is_game_over(self->host))
			break ;
		try_eating(self, self->left, self->right, self->ivals[0]);
		pthread_mutex_lock(&self->lock);
		if (is_game_over(self->host) || self->state == EXIT)
		{
			pthread_mutex_unlock(&self->lock);
			break ;
		}
		pthread_mutex_unlock(&self->lock);
		go_to_bed(self);
		if (is_game_over(self->host))
			break ;
		announcement(self, "is thinking", "\033[93m");
	}
	return (NULL);
}
