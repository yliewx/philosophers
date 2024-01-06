/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 16:58:41 by yliew             #+#    #+#             */
/*   Updated: 2023/12/22 16:59:11 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->write_lock);
	if (!ft_strncmp(status, FINISHED, 19))
	{
		pthread_mutex_lock(&philo->data->meal_lock);
		philo->data->finished_count++;
		pthread_mutex_unlock(&philo->data->meal_lock);
		printf("%lu %i %s %i time(s). [%i/%i]\n",
			current_time() - philo->data->start_time,
			philo->index, status, philo->times_eaten,
			philo->data->finished_count,
			philo->data->total_philos);
	}
	else if (!loop_ended(philo->data))
	{
		printf("%lu %i %s\n",
			current_time() - philo->data->start_time,
			philo->index, status);
	}
	pthread_mutex_unlock(&philo->data->write_lock);
}

void	print_msg(char *message, int fd)
{
	int	i;

	i = 0;
	while (message[i])
	{
		write(fd, &message[i], 1);
		i++;
	}
}

void	end(t_data *data, char *message)
{
	if (message)
		print_msg(message, 2);
	if (data->philos)
	{
		if (data->finished_count == data->total_philos)
		{
			ft_usleep(5);
			pthread_mutex_lock(&data->write_lock);
			printf("All philosophers have finished eating.\n");
			pthread_mutex_unlock(&data->write_lock);
		}
		free(data->philos);
		destroy_mutex(data);
		free(data->forks);
	}
}

void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->total_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->meal_lock);
}
