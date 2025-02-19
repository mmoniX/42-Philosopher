/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:08:44 by mmonika           #+#    #+#             */
/*   Updated: 2025/02/19 15:33:06 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{

	int				total_eat;
	size_t			last_eat;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

typedef struct s_data
{
	int				var1_philonum;
	size_t			var2_die;
	size_t			var3_eat;
	size_t			var4_sleep;
	int				var5_eatnum;
	time_t			start_time;
	int				death;
	int				id;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_status;
	pthread_mutex_t	death_lock;
	t_philo			*philo;
}					t_data;

/* utils */
int		ft_isdigit(char c);
int		ft_atoi(const char *str);
int		ft_strlen(const char *s);
time_t	get_time(void);

/* init */
t_data	*initialize_data(int argc, char *argv[]);
// void	initialize_philosophers(t_data *data, t_philo *philo);

#endif