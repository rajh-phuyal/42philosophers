/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   host.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 21:28:00 by rphuyal           #+#    #+#             */
/*   Updated: 2023/09/12 19:47:06 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

bool	everybody_full(t_host *host, t_table *node, int meals_count)
{
	if (host->max_meals > 0 && \
		meals_count == (host->p_count * host->max_meals))
	{
		send_stop_signal(host);
		pthread_mutex_unlock(&node->lock);
		return (true);
	}
	return (false);
}

bool	starvation(t_host *host, t_table *node)
{
	uint64_t	diff;

	diff = get_diff(host->start_time, node->last_meal);
	if (node->state != EATING && diff >= (uint64_t)host->to_die)
	{
		send_stop_signal(host);
		printf("\033[91m%lu %d %s\n\033[0m",
			get_current_time() - host->start_time, node->id, "died");
		pthread_mutex_unlock(&node->lock);
		return (true);
	}
	return (false);
}

void	check_node_status(t_host *self, t_table *node)
{
	t_table		*next;
	int			meals_count;

	meals_count = 0;
	while (true)
	{
		pthread_mutex_lock(&node->lock);
		if (node->type == FORKNODE)
			continue ;
		if (starvation(self, node))
			return ;
		if (node->meals == self->max_meals)
			node->state = EXIT;
		meals_count += node->meals;
		if (everybody_full(self, node, meals_count))
			return ;
		next = node->left->left;
		if (next == self->table)
			meals_count = 0;
		pthread_mutex_unlock(&node->lock);
		node = next;
	}
}

void	*host_cycle(void *arg)
{
	t_host	*self;

	self = (t_host *)arg;
	if (self->p_count == 1)
		return (NULL);
	check_node_status(self, self->table);
	return (NULL);
}
