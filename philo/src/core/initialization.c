/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 01:47:16 by rphuyal           #+#    #+#             */
/*   Updated: 2023/08/27 19:13:04 by rphuyal          ###   ########.fr       */
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
	host->start_time = get_current_time();
	return (1);
}

void	threads_init(t_host *host)
{
	int			start;
	pthread_t	h_thread;

	start = -1;
	host->threads = malloc(sizeof(pthread_t) * host->p_count);
	pthread_create(&h_thread, NULL, &host_cycle, (void *)host);
	while (++start < host->p_count)
	{
		pthread_create(&host->threads[start],
			NULL, &philo_cycle, (void *)(host->table));
		host->table = (host->table->left)->left;
	}
	while (--start >= 0)
		pthread_join(host->threads[start], NULL);
	pthread_join(h_thread, NULL);
}
