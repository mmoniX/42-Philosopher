/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:27:39 by mmonika           #+#    #+#             */
/*   Updated: 2025/02/18 19:14:30 by mmonika          ###   ########.fr       */
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
	data->death = 0;
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->var1_philonum);
	if (!data->forks)
		return (printf("ERROR: malloc failed\n"), -1);
	pthread_mutex_init(&data->status_lock, NULL);
	pthread_mutex_init(&data->death_lock, NULL);
	return (0);
}

void	initialize_philosophers(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->var1_philonum)
	{
		philo[i].id = i + 1;
		philo[i].total_eat = 0;
		philo[i].last_eat = data->start_time;
		philo[i].data = data;
		pthread_mutex_init(&data->forks[i], NULL);
		philo[i].left_fork = &data->forks[i];
		philo[i].right_fork = &data->forks[(i + 1) % data->var1_philonum];
		i++;
	}
}

