/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:47:20 by rphuyal           #+#    #+#             */
/*   Updated: 2023/09/09 18:47:57 by rphuyal          ###   ########.fr       */
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
