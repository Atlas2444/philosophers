/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leauvray <leauvray@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 01:28:02 by leauvray          #+#    #+#             */
/*   Updated: 2026/01/08 03:43:04 by leauvray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//====INCLUDE-LIBRARY====//
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
//====DEFINE-STRUCT====//
typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	long				last_meal_time;
	int					meals;
	int					died;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	int					num_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int					must_eat;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	t_philo				*philo;
	long				start_time;
	int					someone_died;
}						t_data;

//====DEFINE-PROTO====//

//==parsing.c==//
t_data					*parse_args(int argc, char **argv);
//==init.c==//
int						init_data(t_data *data);
//==utils.c==//
int						ft_atoi(char *str);
//==thread.c==//
int						create_threads(t_data *data);
//==philosopher.c==//
void					*philosopher(void *arg);
void					precise_sleep(t_data *data, long duration);
long					get_time_ms(t_data *data);
int						try_eat(t_philo *philo);
//==philosopher_utils.c==//
void					*handle_one_philo(t_philo *philo);
void					*monitor(void *arg);
#endif