/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 18:43:26 by rphuyal           #+#    #+#             */
/*   Updated: 2023/09/09 03:35:31 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

bool	param_validation(int count, char **params)
{
	if (count < 5 || count > 6)
		return (printf("Error: Wrong number of arguments\n"));
	if (!valid_inputs(count, params))
		return (printf("Invalid arguments! Only pass positive integers!\n"));
	return (0);
}

int	main(int argc, char **argv)
{
	t_host	host;

	if (param_validation(argc, argv))
		return (1);
	if (!initialization(&host, argv, (argc - 5)))
		return (printf("Initialization failed!\n"));
	threads_init(&host);
	liberation(&host);
	return (0);
}
