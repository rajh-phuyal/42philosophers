/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 00:00:20 by rphuyal           #+#    #+#             */
/*   Updated: 2023/08/08 02:27:23 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	*philo_cycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->mutex);
	printf("Philosopher inside mutex executed!!\n");
	pthread_mutex_unlock(&philo->mutex);
	printf("Philosopher outside mutex executed!!\n");
	return (NULL);
}
