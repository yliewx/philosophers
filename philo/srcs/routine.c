/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:23:13 by yliew             #+#    #+#             */
/*   Updated: 2023/12/27 18:23:19 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	dead_philo(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->total_philos)
	{
		if ((current_time() - philos[i].last_meal)
			>= data->time_to_die && !philos[i].is_eating)
		{
			print_status(&philos[i], DIED);
			pthread_mutex_lock(&data->dead_lock);
			data->dead_count++;
			pthread_mutex_unlock(&data->dead_lock);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	all_finished(t_data *data)
{
	pthread_mutex_lock(&data->meal_lock);
	if (data->finished_count == data->total_philos)
		return (pthread_mutex_unlock(&data->meal_lock), true);
	return (pthread_mutex_unlock(&data->meal_lock), false);
}

bool	loop_ended(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	if (data->dead_count > 0)
		return (pthread_mutex_unlock(&data->dead_lock), true);
	pthread_mutex_unlock(&data->dead_lock);
	if (all_finished(data))
		return (true);
	return (false);
}

void	*philo_routine(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	if (philo->index % 2 == 0)
		ft_usleep(1);
	while (1)
	{
		if (!grab_fork(philo) || !go_eat(philo)
			|| !drop_fork(philo) || !go_sleep(philo)
			|| !go_think(philo))
			break ;
	}
	return (NULL);
}

void	*monitor_routine(void *program)
{
	t_data	*data;

	data = (t_data *)program;
	while (1)
	{
		if (dead_philo(data, data->philos) || all_finished(data))
			break ;
	}
	return (NULL);
}
