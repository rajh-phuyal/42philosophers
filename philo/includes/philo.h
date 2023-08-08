/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 18:41:27 by rphuyal           #+#    #+#             */
/*   Updated: 2023/08/08 02:31:06 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

# define EAT 1
# define DIE 4
# define FORK 0
# define SLEEP 2
# define THINK 3

typedef struct s_philo
{
	int				to_eat;
	int				to_die;
	int				to_sleep;
	int				p_count;
	int				max_meals;
	pthread_t		*threads;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*forks;
}	t_philo;

int		ft_atoi(const char *str);
int		valid_inputs(int argc, char **argv);
void	save_inputs(t_philo *philo, char **argv, bool max_meal);

void	*philo_cycle(void *philo);
void	mutexes_initialization(t_philo *philo, int start);
void	threads_initialization(t_philo *philo, int start);

void	liberation(t_philo *philo);

#endif