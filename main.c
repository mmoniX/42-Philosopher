/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:07:23 by mmonika           #+#    #+#             */
/*   Updated: 2025/02/24 12:49:09 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (input_check(argc, argv) != 1)
		return (0);
	initialize_data(&data, argc, argv);
	simulation(data);
	destroy(data);
	return (0);
}
