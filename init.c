/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:27:39 by mmonika           #+#    #+#             */
/*   Updated: 2025/02/23 18:22:18 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize_data(t_data *data, int argc, char *argv[])
{
	int	i;

	i = -1;
	data->var1_philonum = ft_atoi(argv[1]);
	data->var2_die = ft_atoi(argv[2]);
	data->var3_eat = ft_atoi(argv[3]);
	data->var4_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->var5_eatnum = ft_atoi(argv[5]);
	data->var5_eatnum = -1;
	data->start_time = get_time();
	data->death = 0;
	data->threads = malloc(sizeof(pthread_t) * data->var1_philonum);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->var1_philonum);
	data->philosophers = malloc(sizeof(t_philo) * data->var1_philonum);
	while (++i < data->var1_philonum)
	{
		data->philosophers[i].philo_id = i + 1;
		data->philosophers[i].total_eat = 0;
		data->philosophers[i].last_eat = -1;
		pthread_mutex_init(&data->forks[i], NULL);
		data->philosophers[i].left_fork = &data->forks[i];
		data->philosophers[i].right_fork = &data->forks[(i + 1) % data->var1_philonum];
		data->philosophers[i].data = data;
	}
}
/* rules will be the function executed over and over by the philosophers */
void	*rules(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	// philo->last_eat = get_time();
	pthread_create(&philo->status_check, NULL, check_termination, philo->data);
	pthread_detach(philo->status_check);
	if (philo->philo_id % 2 == 0)
		usleep(1000);
	while (!philo->data->death && !check_var5_eatnum(philo->data))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
