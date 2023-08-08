/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liberation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 02:12:01 by rphuyal           #+#    #+#             */
/*   Updated: 2023/08/08 22:51:04 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	free_all_pariticpants(t_table *head)
{
	t_table	*temp;

	temp = head;
	head->right->left = NULL;
	while (head)
	{
		pthread_mutex_destroy(&head->lock);
		temp = head->left;
		free(head);
		head = temp;
	}
}

void	liberation(t_host *host)
{
	if (host->threads)
		free(host->threads);
	if (host->table)
		free_all_pariticpants(host->table);
	pthread_mutex_destroy(&host->print_key);
}
