/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:08:44 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/02 12:07:46 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define RESET	"\e[0m"
# define BLRED	"\e[1m\e[31m"		//dead
# define WHITE	"\e[0;37m"			//fork
# define YELLOW	"\e[0;33m"			//eat
# define BLUE	"\e[0;34m"			//sleep
# define GREEN	"\e[0;32m"			//think

typedef struct s_philo
{
	int				philo_id;
	int				eat;
	int				total_eat;
	time_t			last_eat;
	pthread_t		status_check;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				v1_pnm;
	long			v2_die;
	size_t			v3_eat;
	size_t			v4_sleep;
	int				v5_eatnum;
	time_t			start_time;
	int				death;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	eat_lock;
	t_philo			*philosophers;
}					t_data;

/* utils */
int		ft_isdigit(char c);
int		ft_atoi(const char *str);
int		ft_strlen(const char *s);
time_t	get_time(void);
int		is_dead(t_data *data);

/* init */
int		input_check(int argc, char *argv[]);
void	initialize_data(t_data *data);
void	*check_termination(void *arg);
void	*rules(void *arg);
void	simulation(t_data *data);

/* action */
int		check_var5_eatnum(t_data *data);
int		check_dead(t_data *data);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

/* main */
void	free_all(t_data *data);
// void	one_philo(t_philo *philo);
#endif