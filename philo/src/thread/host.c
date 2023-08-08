/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   host.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 21:28:00 by rphuyal           #+#    #+#             */
/*   Updated: 2023/08/08 22:51:59 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	check_node_status(t_host *host, t_table *head, t_table *iter)
{
	int	m_count;

	m_count = 0;
	while (true)
	{
		if (head == iter && m_count == host->max_meals)
			break ;
		if (head == iter)
			m_count = 0;
		if (iter->state == DEAD)
		{
			printf("%d died\n", iter->id);
			break ;
		}
		m_count += iter->meals;
		iter = iter->left;
	}
}

void	*host_cycle(void *arg)
{
	t_host	*host;

	host = (t_host *)arg;
	check_node_status(host, host->table, host->table);
	return (NULL);
}
