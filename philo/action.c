/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:54:06 by mmonika           #+#    #+#             */
/*   Updated: 2025/02/28 16:13:39 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_var5_eatnum(t_data *data)
{
	int	i;
	int	eat_count;

	i = 0;
	eat_count = 0;
	if (data->var5_eatnum == -1)
		return (0);
	while (i < data->var1_philonum)
	{
		pthread_mutex_lock(&data->eat_lock);
		if (data->philosophers[i].total_eat >= data->var5_eatnum)
			eat_count++;
		pthread_mutex_unlock(&data->eat_lock);
		i++;
	}
	if (eat_count == data->var1_philonum)
	{
		pthread_mutex_lock(&data->death_lock);
		data->death = 1;
		pthread_mutex_unlock(&data->death_lock);
		return (1);
	}
	return (0);
}

int	check_dead(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->var1_philonum)
	{
		pthread_mutex_lock(&data->eat_lock);
		pthread_mutex_lock(&data->death_lock);
		if ((get_time() - data->philosophers[i].last_eat) >= data->var2_die
			&& data->philosophers[i].eat == 0)
		{
			printf(BLRED "%ld	%d	died\n" RESET,
				get_time() - data->start_time, data->philosophers[i].philo_id);
			data->death = 1;
			pthread_mutex_unlock(&data->death_lock);
			pthread_mutex_unlock(&data->eat_lock);
			return (1);
		}
		pthread_mutex_unlock(&data->death_lock);
		pthread_mutex_unlock(&data->eat_lock);
		i++;
	}
	return (0);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (is_dead(philo->data) != 1)
		printf(WHITE "%ld	%d	has taken a fork\n" RESET,
			get_time() - philo->data->start_time, philo->philo_id);
	pthread_mutex_lock(philo->right_fork);
	if (is_dead(philo->data) != 1)
		printf(WHITE "%ld	%d	has taken a fork\n" RESET,
			get_time() - philo->data->start_time, philo->philo_id);
	pthread_mutex_lock(&philo->data->eat_lock);
	philo->eat = 1;
	if (is_dead(philo->data) != 1)
		printf(YELLOW "%ld	%d	is eating\n" RESET,
			get_time() - philo->data->start_time, philo->philo_id);
	philo->last_eat = get_time();
	philo->total_eat++;
	pthread_mutex_unlock(&philo->data->eat_lock);
	usleep(philo->data->var3_eat * 1000);
	philo->eat = 0;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_sleep(t_philo *philo)
{
	if (is_dead(philo->data) != 1)
		printf(BLUE "%ld	%d	is sleeping\n" RESET,
			get_time() - philo->data->start_time, philo->philo_id);
	usleep(philo->data->var4_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	if (is_dead(philo->data) != 1)
		printf(GREEN "%ld	%d	is thinking\n" RESET,
			get_time() - philo->data->start_time, philo->philo_id);
}
