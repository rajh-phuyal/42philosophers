/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 18:43:26 by rphuyal           #+#    #+#             */
/*   Updated: 2023/08/08 02:30:39 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	print_inputs(t_philo *philo)
{
	printf("----------------------\n");
	printf("Philosophers: %d\n", philo->p_count);
	printf("Time to die: %d\n", philo->to_die);
	printf("Time to eat: %d\n", philo->to_eat);
	printf("Time to sleep: %d\n", philo->to_sleep);
	printf("Max meals: %d\n", philo->max_meals);
	printf("----------------------\n");
}

int	main(int argc, char **argv)
{
	t_philo			philo;

	philo.forks = NULL;
	if (argc < 5 || argc > 6)
		return (printf("Error: Wrong number of arguments\n"));
	if (!valid_inputs(argc, argv))
		return (printf("Invalid arguments! Only pass positive integers!\n"));
	save_inputs(&philo, argv, (argc - 5));
	print_inputs(&philo);
	pthread_mutex_init(&(philo.mutex), NULL);
	threads_initialization(&philo, -1);
	pthread_mutex_destroy(&(philo.mutex));
	liberation(&philo);
	return (0);
}
