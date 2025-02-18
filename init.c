/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:27:39 by mmonika           #+#    #+#             */
/*   Updated: 2025/02/18 14:28:31 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initialize_data(t_data *data, int argc, char *argv[])
{
	data->var1_philonum = ft_atoi(argv[1]);
	data->var2_die = ft_atoi(argv[2]);
	data->var3_eat = ft_atoi(argv[3]);
	data->var4_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->var5_eatnum = ft_atoi(argv[5]);
	else
		data->var5_eatnum = -1;
	data->start_time = get_time();
	data->last_eat = get_time();
	data->total_eat = 0;
	return (0);
}

