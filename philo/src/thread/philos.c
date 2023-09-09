/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 00:00:20 by rphuyal           #+#    #+#             */
/*   Updated: 2023/09/09 19:37:10 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	announcement(t_table *self, char *msg, char *color)
{
	uint64_t	diff;

	pthread_mutex_lock(&self->host->key);
	diff = get_current_time() - self->host->start_time;
	if (!self->host->game_over && self->state != EXIT)
		printf("%s%lu %d %s\n\033[0m", color, diff, self->id, msg);
	pthread_mutex_unlock(&self->host->key);
}

void	swap_order(t_table **left, t_table **right)
{
	t_table	*temp;

	temp = *left;
	*left = *right;
	*right = temp;
}
void	try_eating(t_table *self, t_table *left, t_table *right, int e_time)
{
	if ((self->id % 2))
		swap_order(&left, &right);
	pthread_mutex_lock(&left->lock);
	announcement(self, "has taken a fork", "\033[97m");
	pthread_mutex_lock(&right->lock);
	announcement(self, "has taken a fork", "\033[97m");
	announcement(self, "is eating", "\033[92m");
	pthread_mutex_lock(&self->lock);
	self->state = EATING;
	self->meals++;
	self->last_meal = get_current_time();
	pthread_mutex_unlock(&self->lock);
	sleep_phases(e_time);
	pthread_mutex_unlock(&right->lock);
	pthread_mutex_unlock(&left->lock);
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
	if (!(self->id % 2))
		sleep_phases(20);
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
