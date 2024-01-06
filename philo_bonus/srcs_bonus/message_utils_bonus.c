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

#include "philo_bonus.h"

void	print_status(t_philo *philo, char *status)
{
	sem_wait(philo->write_lock->ptr);
	if (!ft_strncmp(status, FINISHED, 19))
	{
		printf("%lu %i %s %i time(s).\n",
			current_time(philo->data) - philo->data->start_time,
			philo->index, status, philo->times_eaten);
	}
	else
	{
		printf("%lu %i %s\n",
			current_time(philo->data) - philo->data->start_time,
			philo->index, status);
	}
	sem_post(philo->write_lock->ptr);
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
