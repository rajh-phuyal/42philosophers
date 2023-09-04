/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 01:47:16 by rphuyal           #+#    #+#             */
/*   Updated: 2023/09/04 12:55:45 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	create_table(t_host *host)
{
	int	i;

	i = (host->p_count * 2) - 1;
	while (i >= 0)
	{
		if (!create_new(host, &host->table, i % 2, (i / 2) + 1))
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
	pthread_mutex_init(&host->key, NULL);
	return (1);
}

void	threads_init(t_host *host)
{
	int	start;

	start = -1;
	host->threads = malloc(sizeof(pthread_t) * host->p_count);
	host->start_time = get_current_time();
	while (++start < host->p_count)
	{
		if (pthread_create(&host->threads[start],
				NULL, &philo_cycle, (void *)(host->table)))
			return ;
		host->table = (host->table->left)->left;
	}
	if (host->p_count == 1)
		return ;
	check_node_status(host, host->table);
}

void	threads_detach(t_host *host)
{
	int	start;

	start = -1;
	while (++start < host->p_count)
	{
		if (pthread_detach(host->threads[start]))
			return ;
	}
}
