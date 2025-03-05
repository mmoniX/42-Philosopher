/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:02:10 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/05 09:05:38 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	input_check(int argc, char *argv[])
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

int	check_var5_eatnum(t_data *data)
{
	int	i;
	int	eat_count;

	i = 0;
	eat_count = 0;
	if (data->v5_eatnum == -1)
		return (0);
	while (i < data->v1_pnm)
	{
		pthread_mutex_lock(&data->eat_lock);
		if (data->philosophers[i].total_eat >= data->v5_eatnum)
			eat_count++;
		pthread_mutex_unlock(&data->eat_lock);
		i++;
	}
	if (eat_count == data->v1_pnm)
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
	while (i < data->v1_pnm)
	{
		pthread_mutex_lock(&data->eat_lock);
		pthread_mutex_lock(&data->death_lock);
		if ((get_time() - data->philosophers[i].last_eat) >= data->v2_die
			&& data->philosophers[i].eat == 0 && data->death != 1)
		{
			data->death = 1;
			printf(BLRED "%ld	%d	died\n" RESET,
				get_time() - data->start_time, data->philosophers[i].philo_id);
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

void	*check_termination(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_var5_eatnum(data) == 1 || check_dead(data) == 1)
		{
			pthread_mutex_lock(&data->death_lock);
			data->death = 1;
			pthread_mutex_unlock(&data->death_lock);
			break ;
		}
	}
	return (NULL);
}
