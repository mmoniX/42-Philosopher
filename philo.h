/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:08:44 by mmonika           #+#    #+#             */
/*   Updated: 2025/02/15 18:58:00 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

int	ft_isdigit(char c);
int	ft_atoi(const char *str);
int	ft_strlen(const char *s);

typedef struct s_data
{
	int				var1_philonum;
	int				var2_die;
	int				var3_eat;
	int				var4_sleep;
	int				var5_eatnum;
	time_t			start_time;
}					t_data;

typedef struct s_prog
{
	
}

#endif