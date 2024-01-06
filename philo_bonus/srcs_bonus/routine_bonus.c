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

#include "philo_bonus.h"

bool	dead_philo(t_data *data, t_philo *philo)
{
	sem_wait(data->dead_lock.ptr);
	if (is_dead(data, philo))
	{
		print_status(philo, DIED);
		sem_post(data->exit_lock.ptr);
		return (true);
	}
	sem_post(data->dead_lock.ptr);
	return (false);
}

bool	is_dead(t_data *data, t_philo *philo)
{
	return ((current_time(data) - philo->last_meal)
		>= data->time_to_die && !philo->is_eating);
}

void	check_finished(t_data *data, t_philo *philo)
{
	if (data->meal_quota != -1 && philo->times_eaten == data->meal_quota)
		sem_post(data->exit_lock.ptr);
}

void	*philo_routine(t_data *data, t_philo *philo)
{
	if (philo->index % 2 == 0)
		ft_usleep(1, data);
	while (1)
	{
		if (!grab_fork(philo) || !go_eat(philo)
			|| !drop_fork(philo) || !go_sleep(philo)
			|| !go_think(philo))
			break ;
	}
	return (data);
}

void	*monitor_routine(void *process)
{
	t_philo	*philo;

	philo = (t_philo *)process;
	while (1)
	{
		if (dead_philo(philo->data, philo) || philo->finished)
			break ;
	}
	return (NULL);
}
