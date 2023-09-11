/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:47:20 by rphuyal           #+#    #+#             */
/*   Updated: 2023/09/11 16:58:22 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	send_stop_signal(t_host *host)
{
	pthread_mutex_lock(&host->key);
	host->game_over = true;
	pthread_mutex_unlock(&host->key);
}

bool	is_game_over(t_host *host)
{
	bool	state;

	pthread_mutex_lock(&host->key);
	state = host->game_over;
	pthread_mutex_unlock(&host->key);
	return (state);
}

void	swap_hands(t_table **left, t_table **right)
{
	t_table	*temp;

	temp = *left;
	*left = *right;
	*right = temp;
}