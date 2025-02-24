/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:54:06 by mmonika           #+#    #+#             */
/*   Updated: 2025/02/24 12:32:49 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_var5_eatnum(t_data *data)
{
	int	i;

	i = 0;
	if (data->var5_eatnum == -1)
		return (0);
	while (i < data->var1_philonum)
	{
		if (data->philosophers[i].total_eat < data->var5_eatnum)
			return (0);
		i++;
	}
	return (1);
}

void	*check_termination(void *arg)
{
	int		i;
	time_t	time_diff;
	t_data	*data;

	data = (t_data *)arg;
	i = 0;
	while (1)
	{
		time_diff = get_time() - data->philosophers[i].last_eat;
		if (check_var5_eatnum(data) == 1)
			break ;
		if (time_diff > data->var2_die
			&& data->philosophers[i].last_eat != -1
			&& check_var5_eatnum(data) != 1)
			{
				printf(BOLDRED "%ld %d died\n" RESET, 
					get_time() - data->start_time, data->philosophers[i].philo_id);
				data->death = 1;
				exit(1);
			}
		if (++i == data->var1_philonum)
			i = 0;	
	}
	return (0);
}

void	philo_eat(t_philo *philo)
{
	time_t	time_diff;
	
	time_diff = get_time() - philo->data->start_time;
	pthread_mutex_lock(philo->left_fork);
	printf(WHITE "%ld %d has taken a fork\n" RESET, time_diff, philo->philo_id);
	if (philo->data->var1_philonum == 1)
	{
		usleep(philo->data->var2_die * 1000);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	printf(WHITE "%ld %d has taken a fork\n" RESET, time_diff, philo->philo_id);
	printf(YELLOW "%ld %d is eating\n" RESET, time_diff, philo->philo_id);
	philo->last_eat = get_time();
	philo->total_eat++;
	usleep(philo->data->var3_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	time_t	time_diff;
	
	time_diff = get_time() - philo->data->start_time;
	printf(BLUE "%ld %d is sleeping\n" RESET, time_diff, philo->philo_id);
	usleep(philo->data->var4_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	time_t	time_diff;
	
	time_diff = get_time() - philo->data->start_time;
	printf(CYAN "%ld %d is thinking\n" RESET, time_diff, philo->philo_id);
}
