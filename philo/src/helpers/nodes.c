/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:49:08 by rphuyal           #+#    #+#             */
/*   Updated: 2023/08/08 19:23:01 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	connect_nodes(t_table **head, t_table *new)
{
	if (head && *head)
	{
		new->next = *head;
		new->prev = (*head)->prev;
		(*head)->prev->next = new;
		(*head)->prev = new;
		*head = new;
		return ;
	}
	new->next = new;
	new->prev = new;
	*head = new;
}

int	create_new(t_host *host, t_table **head, int type)
{
	t_table	*new_node;

	new_node = malloc(sizeof(t_table));
	if (!new_node)
		return (0);
	new_node->type = type;
	new_node->meals = 0;
	new_node->state = IDLE;
	connect_nodes(head, new_node);
	if (type == FORKNODE)
	{
		pthread_mutex_init(&new_node->fork, NULL);
		return (1);
	}
	new_node->meals = 0;
	new_node->state = IDLE;
	new_node->key = &host->print_key;
	new_node->ivals[0] = host->to_die;
	new_node->ivals[1] = host->to_eat;
	new_node->ivals[2] = host->to_sleep;
	return (1);
}
