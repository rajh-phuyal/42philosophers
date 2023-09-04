/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 18:41:27 by rphuyal           #+#    #+#             */
/*   Updated: 2023/09/04 12:54:23 by rphuyal          ###   ########.fr       */
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
# include <stdint.h>

// int arr size to send to processes
# define IVAL 4

// types of nodes in table
# define FORKNODE 1
# define PHILONODE 0

// philo states
# define IDLE 0
# define DEAD 1
# define EXIT -1
# define EATING 2
# define SLEEPING 3
# define THINKING 4

// the host is the main struct that holds all the data
// it holds the params, the threads, the mutexes and the table
// the table is a circular linked list
typedef struct s_host
{
	int				to_die;
	int				to_eat;
	int				to_sleep;
	int				p_count;
	int				max_meals;
	uint64_t		start_time;
	int				total_meals;
	pthread_t		*threads;
	pthread_mutex_t	key;
	struct s_table	*table;
}	t_host;

// each node of the table represent a philo or a fork
// philo nodes have a fork node on their left and right
// fork nodes have a philo node on their left and right
// so the placement of the philos and forks are maintained
typedef struct s_table
{
	int				id;
	int				type;
	int				meals;
	int				state;
	pthread_mutex_t	lock;
	struct timeval	time;
	struct s_table	*left;
	struct s_table	*right;
	struct s_host	*host;
	uint64_t		last_meal;
	int				ivals[IVAL];
}	t_table;

// parsing and param
int			ft_atoi(const char *str);
int			valid_inputs(int argc, char **argv);
void		print_params(t_host *host, bool table);
int			initialization(t_host *host, char **argv, bool max_meal);

// main program functions
void		*host_cycle(void *arg);
void		*philo_cycle(void *arg);
void		threads_init(t_host *host);
void		threads_detach(t_host *host);
void		check_node_status(t_host *self, t_table *node);


// time
uint64_t	get_current_time(void);
int			sleep_phases(useconds_t ms);

// node functions
int			create_new(t_host *host, t_table **head, int type, int id);

// liberate everything allocated
void		liberation(t_host *host);

#endif