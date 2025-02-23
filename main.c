/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:07:23 by mmonika           #+#    #+#             */
/*   Updated: 2025/02/23 14:12:59 by mmonika          ###   ########.fr       */
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

int	main(int argc, char *argv[])
{
	t_data	data;

	if (input_check(argc, argv) != 1)
		return (0);
	initialize_data(&data, argc, argv);
	for (int i = 0; i < data.var1_philonum; i++)
        data.philosophers[i].last_eat = get_time() - (data.var2_die + 100); // Set last_eat to trigger death
	int i = 0;
	while (i < data.var1_philonum)
	{
		printf("%d\n", data.philosophers[i].philo_id);
		i++;
	}
	check_termination(&data);
	return (0);
}
