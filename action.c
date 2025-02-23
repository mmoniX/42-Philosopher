/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:54:06 by mmonika           #+#    #+#             */
/*   Updated: 2025/02/23 13:16:26 by mmonika          ###   ########.fr       */
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

int	check_termination(t_data *data)
{
	int		i;
	time_t	time_diff;

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
					get_time() - data->start_time, data->var1_philonum);
				data->death = 1;
				exit(1);
			}
		if (++i == data->var1_philonum)
			i = 0;	
	}
	return (0);
}
