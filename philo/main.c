/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:07:23 by mmonika           #+#    #+#             */
/*   Updated: 2025/02/28 16:22:03 by mmonika          ###   ########.fr       */
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

void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (is_dead(philo->data) != 1)
		printf(WHITE "%ld	%d	has taken a fork\n" RESET,
			get_time() - philo->data->start_time, philo->philo_id);
	pthread_mutex_unlock(philo->left_fork);
	usleep(philo->data->var2_die * 1000);
	return ;
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (input_check(argc, argv) != 1)
		return (0);
	data.var1_philonum = ft_atoi(argv[1]);
	data.var2_die = ft_atoi(argv[2]);
	data.var3_eat = ft_atoi(argv[3]);
	data.var4_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data.var5_eatnum = ft_atoi(argv[5]);
	else
		data.var5_eatnum = -1;
	initialize_data(&data);
	if (data.var1_philonum == 1)
		one_philo(data.philosophers);
	else
		simulation(&data);
	free_all(&data);
	return (0);
}
