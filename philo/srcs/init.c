/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 15:39:37 by yliew             #+#    #+#             */
/*   Updated: 2023/12/27 15:39:43 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_data *data)
{
	int	i;

	data->forks = malloc(data->total_philos * sizeof(pthread_mutex_t));
	i = 0;
	while (i < data->total_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			data->error = "Failed to initialise forks.\n";
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init(&data->write_lock, NULL)
		|| pthread_mutex_init(&data->dead_lock, NULL)
		|| pthread_mutex_init(&data->meal_lock, NULL))
	{
		data->error = "Failed to initialise mutexes.\n";
		return (0);
	}
	return (1);
}

int	init_threads(t_data *data, t_philo **philos)
{
	int	i;

	if (pthread_create(&data->monitor, NULL, monitor_routine, data))
	{
		data->error = "Failed to initialise monitoring thread.\n";
		return (0);
	}
	i = 0;
	while (i < data->total_philos)
	{
		if (pthread_create(&(*philos)[i].thread_id, NULL,
			philo_routine, &(*philos)[i]))
		{
			data->error = "Failed to initialise threads.\n";
			return (0);
		}
		i++;
	}
	return (1);
}

int	join_threads(t_data *data)
{
	int	i;

	if (pthread_join(data->monitor, NULL))
	{
		data->error = "Failed to join monitoring thread.\n";
		return (0);
	}
	i = 0;
	while (i < data->total_philos)
	{
		if (pthread_join(data->philos[i].thread_id, NULL))
		{
			data->error = "Failed to join threads.\n";
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_philosophers(t_data *data)
{
	int	i;

	data->philos = malloc(data->total_philos * sizeof(t_philo));
	if (!data->philos)
	{
		data->error = "Failed to allocate memory for philosophers.\n";
		return (0);
	}
	i = 0;
	while (i < data->total_philos)
	{
		data->philos[i].index = i + 1;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].times_eaten = 0;
		data->philos[i].is_eating = false;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1)
			% data->total_philos];
		data->philos[i].data = data;
		i++;
	}
	return (1);
}
