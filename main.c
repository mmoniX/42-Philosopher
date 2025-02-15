/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:07:23 by mmonika           #+#    #+#             */
/*   Updated: 2025/02/15 15:35:30 by mmonika          ###   ########.fr       */
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
		if (ft_atoi(argv[i]) <= 0 || ft_strlen(argv[i]) >= 11)  //not sure if all variables will be > 0 (var 6)
			return (printf("ERROR: not positive input\n"), -1);
		i++;
	}
	return (1);
}

t_table initialization 

	
int	main(int argc, char *argv[])
{
	pthread_t	thread;
	if (input_check(argc, argv) != 1)
		return (0);
	pthread_create(&thread, NULL, &val, NULL);
	pthread_join(thread, NULL);
	return (0);
}
