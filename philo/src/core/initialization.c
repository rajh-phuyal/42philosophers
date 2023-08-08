/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 01:47:16 by rphuyal           #+#    #+#             */
/*   Updated: 2023/08/08 02:31:59 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	save_inputs(t_philo *philo, char **argv, bool max_meal)
{
	philo->p_count = ft_atoi(argv[1]);
	philo->to_die = ft_atoi(argv[2]);
	philo->to_eat = ft_atoi(argv[3]);
	philo->to_sleep = ft_atoi(argv[4]);
	if (max_meal)
		philo->max_meals = ft_atoi(argv[5]);
	else
		philo->max_meals = -1;
}

void	mutexes_initialization(t_philo *philo, int start)
{
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->p_count);
	while (++start < philo->p_count)
		pthread_mutex_init(&philo->forks[start], NULL);
	while (--start >= 0)
		pthread_mutex_destroy(&philo->forks[start]);
}

void	threads_initialization(t_philo *philo, int start)
{
	philo->threads = malloc(sizeof(pthread_t) * philo->p_count);
	while (++start < philo->p_count)
		pthread_create(&philo->threads[start],
			NULL, &philo_cycle, (void *)&philo);
	while (--start >= 0)
		pthread_join(philo->threads[start], NULL);
}
