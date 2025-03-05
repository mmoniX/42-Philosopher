/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:27:39 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/05 09:06:03 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize_data(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	data->death = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->v1_pnm);
	data->philosophers = malloc(sizeof(t_philo) * data->v1_pnm);
	pthread_mutex_init(&data->death_lock, NULL);
	pthread_mutex_init(&data->eat_lock, NULL);
	while (i < data->v1_pnm)
	{
		data->philosophers[i].philo_id = i + 1;
		data->philosophers[i].total_eat = 0;
		data->philosophers[i].last_eat = data->start_time;
		data->philosophers[i].eat = 0;
		data->philosophers[i].data = data;
		pthread_mutex_init(&data->forks[i], NULL);
		data->philosophers[i].left_fork = &data->forks[i];
		data->philosophers[i].right_fork = &data->forks[(i + 1) % data->v1_pnm];
		i++;
	}
}

int	is_dead(t_data *data)
{
	pthread_mutex_lock(&data->death_lock);
	if (data->death == 1)
	{
		pthread_mutex_unlock(&data->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->death_lock);
	return (0);
}

/* function for each philosopher */
void	*rules(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 == 0)
		ft_usleep(1);
	while (is_dead(philo->data) != 1)
	{
		take_fork(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

/* function for the whole */
void	simulation(t_data *data)
{
	int			i;
	pthread_t	threads;

	i = 0;
	pthread_create(&threads, NULL, &check_termination, data);
	while (i < data->v1_pnm)
	{
		pthread_create(&data->philosophers[i].status_check,
			NULL, &rules, &data->philosophers[i]);
		i++;
	}
	i = 0;
	pthread_join(threads, NULL);
	while (i < data->v1_pnm)
	{
		pthread_join(data->philosophers[i].status_check, NULL);
		i++;
	}
}

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->death_lock);
	pthread_mutex_destroy(&data->eat_lock);
	while (i < data->v1_pnm)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	if (data->forks)
		free(data->forks);
	if (data->philosophers)
		free(data->philosophers);
}
