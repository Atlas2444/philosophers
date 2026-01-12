/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leauvray <leauvray@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 04:25:18 by leauvray          #+#    #+#             */
/*   Updated: 2026/01/08 03:41:33 by leauvray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_data_values(t_data *data, int argc, char **argv)
{
	data->num_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
}

static int	validate_data(t_data *data, int argc)
{
	if (data->num_philo <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
	{
		printf("error : All values must be positive\n");
		return (1);
	}
	if (argc == 6 && data->must_eat <= 0)
	{
		printf("error : All values must be positive\n");
		return (1);
	}
	return (0);
}

t_data	*parse_args(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
	{
		printf("error : Invalid number of arguments\n");
		return (NULL);
	}
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	set_data_values(data, argc, argv);
	if (validate_data(data, argc))
	{
		free(data);
		return (NULL);
	}
	data->someone_died = 0;
	data->start_time = 0;
	data->philo = NULL;
	data->forks = NULL;
	return (data);
}
