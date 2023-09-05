/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   host.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 21:28:00 by rphuyal           #+#    #+#             */
/*   Updated: 2023/09/05 21:59:52 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	send_stop_signal(t_host *host)
{
	pthread_mutex_lock(&host->key);
	host->game_over = true;
	pthread_mutex_unlock(&host->key);
}

// void	empty_spagetti_bowl(t_table *host)
// {
// 	return ;
// }

bool	starvation(t_table *host, t_table *node)
{
	uint64_t	diff;

	diff = get_diff(host->start_time, node->last_meal);
	if (node->state != EATING && diff >= (uint64_t)host->to_die)
	{
		send_stop_signal(host);
		printf("%lu %d %s\n", get_current_time() - host->start_time,
			node->id, "died");
		pthread_mutex_unlock(&node->lock);
		return (true);
	}
	return (false);
}

void	check_node_status(t_host *self, t_table *node)
{
	t_table		*next;
	int			meals_count;
	uint64_t	diff;

	while (true)
	{
		pthread_mutex_lock(&node->lock);
		if (node->type == FORKNODE)
			continue ;
		if (starvation(self, node))
			return ;
		meals_count += node->meals;
		if (node->meals == self->max_meals)
			node->state = EXIT;
		next = node->left->left;
		if (next == host->table)
		{
			if (empty_spagetti_bowl(host, meals_count))
				return ;
			meals_count = 0
		}
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
