/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:54:06 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/05 09:15:10 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (is_dead(philo->data) != 1)
		printf(WHITE "%ld	%d	has taken a fork\n" RESET,
			get_time() - philo->data->start_time, philo->philo_id);
	if (philo->data->v1_pnm == 1)
	{
		ft_usleep(philo->data->v2_die);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	if (is_dead(philo->data) != 1)
		printf(WHITE "%ld	%d	has taken a fork\n" RESET,
			get_time() - philo->data->start_time, philo->philo_id);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eat_lock);
	philo->eat = 1;
	if (is_dead(philo->data) != 1)
		printf(YELLOW "%ld	%d	is eating\n" RESET,
			get_time() - philo->data->start_time, philo->philo_id);
	philo->last_eat = get_time();
	philo->total_eat++;
	pthread_mutex_unlock(&philo->data->eat_lock);
	ft_usleep(philo->data->v3_eat);
	philo->eat = 0;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	if (is_dead(philo->data) != 1)
		printf(BLUE "%ld	%d	is sleeping\n" RESET,
			get_time() - philo->data->start_time, philo->philo_id);
	ft_usleep(philo->data->v4_sleep);
}

void	philo_think(t_philo *philo)
{
	if (is_dead(philo->data) != 1)
		printf(GREEN "%ld	%d	is thinking\n" RESET,
			get_time() - philo->data->start_time, philo->philo_id);
}
