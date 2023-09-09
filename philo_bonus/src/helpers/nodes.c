/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:49:08 by rphuyal           #+#    #+#             */
/*   Updated: 2023/09/09 03:26:31 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	connect_nodes(t_table **head, t_table *new)
{
	if (head && *head)
	{
		new->left = *head;
		new->right = (*head)->right;
		(*head)->right->left = new;
		(*head)->right = new;
		*head = new;
		return ;
	}
	new->left = new;
	new->right = new;
	*head = new;
}

int	create_new(t_host *host, t_table **head, int type, int id)
{
	t_table	*new_node;

	new_node = malloc(sizeof(t_table));
	if (!new_node)
		return (0);
	new_node->id = id;
	new_node->meals = 0;
	new_node->type = type;
	new_node->host = host;
	new_node->state = IDLE;
	new_node->last_meal = 0;
	connect_nodes(head, new_node);
	new_node->ivals[0] = host->to_eat;
	new_node->ivals[1] = host->to_sleep;
	pthread_mutex_init(&new_node->lock, NULL);
	return (1);
}
