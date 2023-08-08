/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 01:47:16 by rphuyal           #+#    #+#             */
/*   Updated: 2023/08/08 19:41:09 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	destroy_all_mutexes(t_host *host, t_table *node)
{
	while (node != host->table)
	{
		if (node->type == FORKNODE)
			pthread_mutex_destroy(&node->fork);
		node = node->left;
	}
	pthread_mutex_destroy(&host->print_key);
}

int	create_table(t_host *host)
{
	int	i;

	i = (host->p_count * 2) - 1;
	while (i >= 0)
	{
		if (!create_new(host, &host->table, i % 2))
			return (0);
		i--;
	}
	return (1);
}

int	initialization(t_host *host, char **argv, bool max_meal)
{
	host->p_count = ft_atoi(argv[1]);
	host->to_die = ft_atoi(argv[2]);
	host->to_eat = ft_atoi(argv[3]);
	host->to_sleep = ft_atoi(argv[4]);
	if (max_meal)
		host->max_meals = ft_atoi(argv[5]);
	else
		host->max_meals = -1;
	host->table = NULL;
	if (!create_table(host))
		return (0);
	return (1);
}

void	threads_init(t_host *host)
{
	int	start;

	start = -1;
	host->threads = malloc(sizeof(pthread_t) * host->p_count);
	while (++start < host->p_count)
	{
		pthread_create(&host->threads[start],
			NULL, &philo_cycle, (void *)&(host->table));
		host->table = (host->table->left)->left;
	}
	while (--start >= 0)
		pthread_join(host->threads[start], NULL);
}
