/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leauvray <leauvray@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 08:11:00 by leauvray          #+#    #+#             */
/*   Updated: 2026/01/08 03:43:04 by leauvray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(t_data *data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - data->start_time);
}

void	precise_sleep(t_data *data, long duration)
{
	long	start;

	start = get_time_ms(data);
	while (get_time_ms(data) - start < duration && !data->someone_died)
	{
		usleep(50);
	}
}

static int	take_forks(t_philo *philo, int *left, int *right)
{
	t_data	*data;

	data = philo->data;
	*left = philo->id - 1;
	*right = philo->id % data->num_philo;
	pthread_mutex_lock(&data->forks[*left]);
	if (data->someone_died)
	{
		pthread_mutex_unlock(&data->forks[*left]);
		return (0);
	}
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld %d has taken a fork\n", get_time_ms(data),
		philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_lock(&data->forks[*right]);
	if (data->someone_died)
	{
		pthread_mutex_unlock(&data->forks[*right]);
		pthread_mutex_unlock(&data->forks[*left]);
		return (0);
	}
	return (1);
}

int	try_eat(t_philo *philo)
{
	t_data	*data;
	int		left_fork;
	int		right_fork;

	data = philo->data;
	if (!take_forks(philo, &left_fork, &right_fork))
		return (0);
	philo->last_meal_time = get_time_ms(data);
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld %d has taken a fork\n", get_time_ms(data),
		philo->id);
	printf("%ld %d is eating [%d]\n", get_time_ms(data),
		philo->id, philo->meals);
	pthread_mutex_unlock(&data->print_mutex);
	precise_sleep(data, data->time_to_eat);
	pthread_mutex_unlock(&data->forks[right_fork]);
	pthread_mutex_unlock(&data->forks[left_fork]);
	philo->meals++;
	return (1);
}

void	*philosopher(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (data->num_philo == 1)
		return (handle_one_philo(philo));
	while (!data->someone_died)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("%ld %d is thinking\n", get_time_ms(data),
			philo->id);
		pthread_mutex_unlock(&data->print_mutex);
		if (!try_eat(philo))
			break ;
		pthread_mutex_lock(&data->print_mutex);
		printf("%ld %d is sleeping\n", get_time_ms(data),
			philo->id);
		pthread_mutex_unlock(&data->print_mutex);
		precise_sleep(data, data->time_to_sleep);
	}
	return (NULL);
}
