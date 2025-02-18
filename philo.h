/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:08:44 by mmonika           #+#    #+#             */
/*   Updated: 2025/02/18 14:38:24 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				id;
	int				var1_philonum;
	size_t			var2_die;
	size_t			var3_eat;
	size_t			var4_sleep;
	int				var5_eatnum;
	time_t			start_time;
	time_t			last_eat;
	int				total_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_data;

typedef struct s_prog
{
	t_data			*data;
}					t_prog;

/* utils */
int	ft_isdigit(char c);
int	ft_atoi(const char *str);
int	ft_strlen(const char *s);

/* init */
int	initialize_data(t_data *data, int argc, char *argv[]);

#endif