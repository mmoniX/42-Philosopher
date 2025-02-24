/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:27:39 by mmonika           #+#    #+#             */
/*   Updated: 2025/02/24 16:10:11 by mmonika          ###   ########.fr       */
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
/* function for each philosopher */
void	*rules(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	philo->last_eat = get_time();
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

/* function for the whole */
void	simulation(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->var1_philonum)
	{
		pthread_create(&data->threads[i], NULL, rules, &data->philosophers[i]);
		i++;
	}
	i = 0;
	while (i < data->var1_philonum)
	{
		pthread_join(data->threads[i], NULL);
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
	if (data->threads)
		free(data->threads);
	if (data->forks)
		free(data->forks);
	if (data->philosophers)
		free(data->philosophers);
}
