/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rajphuyal <rajphuyal@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:24:06 by rphuyal           #+#    #+#             */
/*   Updated: 2023/09/10 20:23:33 by rajphuyal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	print_table(t_table *head, t_table *start)
{
	while (true)
	{
		printf("=======================\n");
		printf("ID: %d\n", start->id);
		if (start->type == FORKNODE)
			printf("FORK NODE\n");
		else
			printf("PHILO NODE\n");
		printf("Meals: %d\n", start->meals);
		printf("State: %d\n", start->state);
		printf("Next: %p\n", start->left);
		if (start->left->type == FORKNODE)
			printf("TO LEFT IS FORK NODE\n");
		else
			printf("TO LEFT IS PHILO NODE\n");
		printf("Prev: %p\n", start->right);
		if (start->right->type == FORKNODE)
			printf("TO RIGHT IS FORK NODE\n");
		else
			printf("TO RIGHT IS PHILO NODE\n");
		printf("=======================\n\n");
		start = start->left;
		if (start == head)
			break ;
	}
}

void	print_ivals(int *ivals, int start)
{
	while (start < 2)
	{
		printf("ivals[%d]: %d\n", start, ivals[start]);
		start++;
	}
}

void	print_params(t_host *host, bool table)
{
	printf("----------------------\n");
	printf("philosophers: %d\n", host->p_count);
	printf("Time to die: %d\n", host->to_die);
	printf("Time to eat: %d\n", host->to_eat);
	printf("Time to sleep: %d\n", host->to_sleep);
	printf("Max meals: %d\n", host->max_meals);
	printf("Start time: %llu\n", host->start_time);
	if (table)
	{
		printf("----------ROUND TABLE---------\n");
		print_table(host->table, host->table);
	}
	print_ivals(host->table->ivals, 0);
	printf("----------------------\n");
}
