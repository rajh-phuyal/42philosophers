/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 18:43:26 by rphuyal           #+#    #+#             */
/*   Updated: 2023/08/06 02:07:46 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (printf("Error: Wrong number of arguments\n"));
	if (!valid_inputs(argc, argv))
		return (printf("Invalid arguments! Only pass positive integers!\n"));
	return (0);
}
