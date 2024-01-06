/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:51:24 by yliew             #+#    #+#             */
/*   Updated: 2024/01/06 16:51:33 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_all_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->total_philos)
	{
		waitpid(data->philos[i].pid, NULL, 0);
		i++;
	}
	sem_post(data->exit_lock.ptr);
}

void	end_processes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->total_philos)
	{
		kill(data->philos[i].pid, SIGTERM);
		i++;
	}
}

void	close_semaphores(t_data *data)
{
	sem_close(data->forks.ptr);
	sem_close(data->write_lock.ptr);
	sem_close(data->dead_lock.ptr);
	sem_close(data->exit_lock.ptr);
}

void	unlink_semaphores(void)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_EXIT);
}

void	end(t_data *data, char *message, int exit_code)
{
	if (message)
		print_msg(message, 2);
	if (data->philos)
	{
		close_semaphores(data);
		unlink_semaphores();
		end_processes(data);
		free(data->philos);
	}
	exit(exit_code);
}
