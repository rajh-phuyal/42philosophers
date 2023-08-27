/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   host.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 21:28:00 by rphuyal           #+#    #+#             */
/*   Updated: 2023/08/27 19:03:47 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	check_node_status(t_host *self, t_table *head, t_table *iter)
{
	int	m_count;

	m_count = 0;
	while (true)
	{
		if (head == iter && m_count == self->max_meals)
			break ;
		if (head == iter)
		{
			pthread_mutex_lock(&self->key);
			self->total_meals = m_count;
			pthread_mutex_unlock(&self->key);
			m_count = 0;
		}
		if (iter->state == DEAD)
		{
			printf("%d dieddddd\n", iter->id);
			break ;
		}
		m_count += iter->meals;
		iter = iter->left;
	}
}

void	*host_cycle(void *arg)
{
	t_host	*self;

	self = (t_host *)arg;
	check_node_status(self, self->table, self->table);
	return (NULL);
}
