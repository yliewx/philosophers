/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:22:24 by yliew             #+#    #+#             */
/*   Updated: 2023/12/27 18:22:31 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	grab_fork(t_philo *philo)
{
	sem_wait(philo->forks->ptr);
	if (is_dead(philo->data, philo))
		return (0);
	print_status(philo, GRAB_FORK);
	if (philo->data->total_philos == 1)
	{
		ft_usleep(philo->data->time_to_die, philo->data);
		return (0);
	}
	sem_wait(philo->forks->ptr);
	if (is_dead(philo->data, philo))
		return (0);
	print_status(philo, GRAB_FORK);
	return (1);
}

int	go_eat(t_philo *philo)
{
	if (is_dead(philo->data, philo))
		return (0);
	philo->is_eating = true;
	philo->last_meal = current_time(philo->data);
	philo->times_eaten++;
	print_status(philo, EAT);
	ft_usleep(philo->data->time_to_eat, philo->data);
	philo->is_eating = false;
	return (1);
}

int	drop_fork(t_philo *philo)
{
	sem_post(philo->forks->ptr);
	sem_post(philo->forks->ptr);
	if (is_dead(philo->data, philo))
		return (0);
	if (philo->times_eaten == philo->data->meal_quota)
	{
		print_status(philo, FINISHED);
		philo->finished = true;
		return (0);
	}
	return (1);
}

int	go_sleep(t_philo *philo)
{
	if (is_dead(philo->data, philo))
		return (0);
	print_status(philo, SLEEP);
	ft_usleep(philo->data->time_to_sleep, philo->data);
	return (1);
}

int	go_think(t_philo *philo)
{
	if (is_dead(philo->data, philo))
		return (0);
	print_status(philo, THINK);
	ft_usleep(1, philo->data);
	return (1);
}
