/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leauvray <leauvray@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:32:07 by leauvray          #+#    #+#             */
/*   Updated: 2026/01/08 03:34:41 by leauvray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (!data->philo[i].died && data->philo[i].last_meal_time != 0)
		{
			if (get_time_ms(data) - data->philo[i].last_meal_time
				> data->time_to_die)
			{
				pthread_mutex_lock(&data->print_mutex);
				printf("%ld %d died\n", get_time_ms(data),
					data->philo[i].id);
				pthread_mutex_unlock(&data->print_mutex);
				data->philo[i].died = 1;
				data->someone_died = 1;
				return (1);
			}
		}
		i++;
	}
	return (0);
}

static int	check_meals(t_data *data)
{
	int	i;
	int	n;

	if (data->must_eat == -1)
		return (0);
	i = 0;
	n = 0;
	while (i < data->num_philo)
	{
		if (data->philo[i].meals >= data->must_eat)
			n++;
		i++;
	}
	if (n == data->num_philo)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("%ld all philo eat enought\n", get_time_ms(data));
		pthread_mutex_unlock(&data->print_mutex);
		data->someone_died = 1;
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!data->someone_died)
	{
		if (check_death(data))
			return (NULL);
		if (check_meals(data))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
