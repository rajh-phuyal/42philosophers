/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   host.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 21:28:00 by rphuyal           #+#    #+#             */
/*   Updated: 2023/08/28 20:24:44 by rphuyal          ###   ########.fr       */
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

void	send_stop_signal(t_table *head)
{
	pthread_mutex_lock(&head->lock);
	while (head->left != head)
	{
		head = head->left;
		head->state = DEAD;
		pthread_mutex_unlock(&head->lock);
	}
}

void	check_node_status(t_host *self, t_table *node)
{
	uint64_t	diff;

	while (true)
	{
		if (node->state == DEAD)
			break ;
		diff = get_diff(self->start_time, node->last_meal);
		if (node->state != EATING && diff > (uint64_t)node->ivals[0])
		{
			pthread_mutex_lock(&node->lock);
			node->state = DEAD;
			send_stop_signal(self->table);
			pthread_mutex_unlock(&node->lock);
			break ;
		}
		if (node->meals == self->max_meals)
		{
			pthread_mutex_lock(&node->lock);
			printf("Philosopher %d has eaten %d times\n", node->id, node->meals);
			node->state = IDLE;
			pthread_mutex_unlock(&node->lock);
		}
		node = node->left;
		printf("here\n");
	}
}

void	*host_cycle(void *arg)
{
	t_host	*self;

	self = (t_host *)arg;
	check_node_status(self, self->table);
	return (NULL);
}
