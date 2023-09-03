/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   host.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 21:28:00 by rphuyal           #+#    #+#             */
/*   Updated: 2023/09/03 18:46:34 by rphuyal          ###   ########.fr       */
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

void	announce_death(uint64_t diff, int id, char *msg)
{
	printf("%lu %d %s\n", diff, id, msg);
}

void	check_node_status(t_host *self, t_table *node)
{
	uint64_t	diff;

	while (true)
	{
		diff = get_diff(self->start_time, node->last_meal);
		// printf("diff: %lu\n", diff);
		if (node->state != EATING && diff >= (uint64_t)node->ivals[0])
		{
			pthread_mutex_lock(&node->lock);
			node->state = DEAD;
			announce_death(get_current_time() - self->start_time,
				node->id, "died");
			pthread_mutex_unlock(&node->lock);
			send_stop_signal(node, node);
			return ;
		}
		if (node->meals == self->max_meals)
		{
			pthread_mutex_lock(&node->lock);
			node->state = EXIT;
			pthread_mutex_unlock(&node->lock);
		}
		node = node->left;
	}
}
