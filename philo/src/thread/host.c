/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   host.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 21:28:00 by rphuyal           #+#    #+#             */
/*   Updated: 2023/09/04 17:23:21 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

uint64_t	get_diff(uint64_t start, uint64_t last)
{
	if (last > 0)
		return (get_current_time() - last);
	else
		return (get_current_time() - start);
}

void	send_stop_signal(t_table *head, t_table *node)
{
	t_table	*left;

	while (true)
	{
		node->state = EXIT;
		left = node->left;
		if (left == head)
			break ;
		node = left;
	}
}

void	check_node_status(t_host *self, t_table *node)
{
	t_table		*next;
	uint64_t	diff;

	while (true)
	{
		pthread_mutex_lock(&node->lock);
		if (node->type == FORKNODE)
			continue ;
		diff = get_diff(self->start_time, node->last_meal);
		if (node->state != EATING && diff >= (uint64_t)self->to_die)
		{
			printf("%lu %d %s\n", get_current_time() - self->start_time,
				node->id, "died");
			send_stop_signal(node, node);
			return ;
		}
		if (node->meals == self->max_meals)
			node->state = EXIT;
		next = node->left->left;
		pthread_mutex_unlock(&node->lock);
		node = next;
	}
}

void	*host_cycle(void *arg)
{
	t_host	*self;

	self = (t_host *)arg;
	check_node_status(self, self->table);
	return (NULL);
}
