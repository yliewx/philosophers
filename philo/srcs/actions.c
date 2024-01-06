/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:22:24 by yliew             #+#    #+#             */
/*   Updated: 2023/12/27 18:22:31 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	grab_fork(t_philo *philo)
{
	if (loop_ended(philo->data))
		return (0);
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, GRAB_FORK);
	if (philo->data->total_philos == 1)
	{
		ft_usleep(philo->data->time_to_die);
		print_status(philo, DIED);
		return (0);
	}
	if (loop_ended(philo->data))
		return (0);
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, GRAB_FORK);
	return (1);
}

int	go_eat(t_philo *philo)
{
	if (loop_ended(philo->data))
		return (0);
	philo->is_eating = true;
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal = current_time();
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->data->meal_lock);
	print_status(philo, EAT);
	ft_usleep(philo->data->time_to_eat);
	philo->is_eating = false;
	return (1);
}

int	drop_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (loop_ended(philo->data))
		return (0);
	if (philo->times_eaten == philo->data->meal_quota)
	{
		print_status(philo, FINISHED);
		if (philo->data->finished_count == philo->data->total_philos)
			return (0);
	}
	return (1);
}

int	go_sleep(t_philo *philo)
{
	if (loop_ended(philo->data))
		return (0);
	print_status(philo, SLEEP);
	ft_usleep(philo->data->time_to_sleep);
	return (1);
}

int	go_think(t_philo *philo)
{
	if (loop_ended(philo->data))
		return (0);
	print_status(philo, THINK);
	return (1);
}
