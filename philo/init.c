/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:27:39 by mmonika           #+#    #+#             */
/*   Updated: 2025/02/27 15:17:15 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int input_check(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 1;
	if (argc < 5 || argc > 6)
		return (printf("ERROR: check arguments number\n"), -1);
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (printf("ERROR: invalid input\n"), -1);
			j++;
		}
		if (i == 5 && (ft_atoi(argv[i]) < 0 || ft_strlen(argv[i]) >= 11))
			return (printf("ERROR: check arguments\n"), -1);
		else if (ft_atoi(argv[i]) <= 0 || ft_strlen(argv[i]) >= 11)
			return (printf("ERROR: not positive input\n"), -1);
		i++;
	}
	return (1);
}

void	initialize_data(t_data *data, char *argv[], int argc)
{
	int	i;

	i = 0;
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
	data->threads = malloc(sizeof(pthread_t) * data->var1_philonum);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->var1_philonum);
	data->philosophers = malloc(sizeof(t_philo) * data->var1_philonum);
	pthread_mutex_init(&data->death_lock, NULL);
	pthread_mutex_init(&data->eat_lock, NULL);
	while (i < data->var1_philonum)
	{
		data->philosophers[i].philo_id = i + 1;
		data->philosophers[i].total_eat = 0;
		data->philosophers[i].last_eat = data->start_time;
		data->philosophers[i].data = data;
		pthread_mutex_init(&data->forks[i], NULL);
		data->philosophers[i].left_fork = &data->forks[i];
		data->philosophers[i].right_fork = &data->forks[(i + 1) % data->var1_philonum];
		i++;
	}
}
/* function for each philosopher */
void	*rules(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_lock);
		if (philo->data->death == 1)
		{
			pthread_mutex_unlock(&philo->data->death_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->death_lock);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	*check_termination(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_var5_eatnum(data) == 1 || check_dead(data) == 1)
			break ;
	}
	return (NULL);
}

/* function for the whole */
void	simulation(t_data *data)
{
	int	i;

	i = 0;
	pthread_create(&data->threads, NULL, &check_termination, data);
	while (i < data->var1_philonum)
	{
		pthread_create(&data->philosophers[i].status_check, NULL, &rules, &data->philosophers[i]);
		i++;
	}
	i = 0;
	pthread_join(data->threads, NULL);
	while (i < data->var1_philonum)
	{
		pthread_join(data->philosophers[i].status_check, NULL);
		i++;
	}
}

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->var1_philonum)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->death_lock);
	pthread_mutex_destroy(&data->eat_lock);
	if (data->threads)
		free(data->threads);
    if (data->forks)
        free(data->forks);
    if (data->philosophers)
        free(data->philosophers);
}
