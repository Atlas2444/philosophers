/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leauvray <leauvray@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 07:47:00 by leauvray          #+#    #+#             */
/*   Updated: 2026/01/08 03:39:55 by leauvray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	free(data->philo);
	free(data->forks);
	free(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = parse_args(argc, argv);
	if (!data)
		return (1);
	if (init_data(data) == 1)
	{
		printf("Error initializing data\n");
		free(data);
		return (1);
	}
	if (create_threads(data) == 1)
	{
		printf("Error creating threads\n");
		return (1);
	}
	cleanup(data);
	return (0);
}
