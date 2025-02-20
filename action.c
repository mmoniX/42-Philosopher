/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:54:06 by mmonika           #+#    #+#             */
/*   Updated: 2025/02/20 17:30:24 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_var5_eatnum(t_data *data)
{
	int	i;

	i = 0;
	if (data->var5_eatnum == -1)
		return (1);
	while (i < data->var1_philonum)
	{
		if (data->philosophers[i].total_eat < data->var5_eatnum)
			return (1);
		i++;
	}
	return (0);
}

// void	actions(t_data *data)
// {
// 	if (check_var5_eatnum != 0)
// 	{
		
// 	}
// }