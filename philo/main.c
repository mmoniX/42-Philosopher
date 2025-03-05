/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:07:23 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/05 09:06:28 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (input_check(argc, argv) != 1)
		return (0);
	data.v1_pnm = ft_atoi(argv[1]);
	data.v2_die = ft_atoi(argv[2]);
	data.v3_eat = ft_atoi(argv[3]);
	data.v4_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data.v5_eatnum = ft_atoi(argv[5]);
	else
		data.v5_eatnum = -1;
	initialize_data(&data);
	simulation(&data);
	free_all(&data);
	return (0);
}
