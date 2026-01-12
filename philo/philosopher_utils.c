/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leauvray <leauvray@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 04:00:00 by leauvray          #+#    #+#             */
/*   Updated: 2026/01/08 04:00:00 by leauvray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*handle_one_philo(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld %d is thinking\n", get_time_ms(data),
		philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_lock(&data->forks[0]);
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld %d has taken a fork\n", get_time_ms(data),
		philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	precise_sleep(data, data->time_to_die);
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld %d died\n", get_time_ms(data), philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	philo->died = 1;
	data->someone_died = 1;
	return (NULL);
}
