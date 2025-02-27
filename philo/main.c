/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:07:23 by mmonika           #+#    #+#             */
/*   Updated: 2025/02/27 16:13:45 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->death_lock);
	pthread_mutex_destroy(&data->eat_lock);
	while (i < data->var1_philonum)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	if (data->forks)
		free(data->forks);
	if (data->philosophers)
		free(data->philosophers);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (input_check(argc, argv) != 1)
		return (0);
	initialize_data(&data, argv, argc);
	simulation(&data);
	free_all(&data);
	return (0);
}
