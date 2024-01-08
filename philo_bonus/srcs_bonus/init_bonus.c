/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 15:39:37 by yliew             #+#    #+#             */
/*   Updated: 2023/12/27 15:39:43 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_sem(t_data *data, t_sem *sem, char *name, int value)
{
	sem->name = name;
	sem->ptr = sem_open(name, O_CREAT | O_EXCL, S_IRWXU, value);
	if (sem->ptr == SEM_FAILED)
		end(data, "Failed to create semaphore.\n", 1, parent);
}

void	init_semaphores(t_data *data)
{
	unlink_semaphores();
	create_sem(data, &data->forks, SEM_FORKS, data->total_philos);
	create_sem(data, &data->write_lock, SEM_WRITE, 1);
	create_sem(data, &data->dead_lock, SEM_DEAD, 1);
	create_sem(data, &data->exit_lock, SEM_EXIT, 0);
}

void	init_philo_struct(t_data *data, t_philo *philo, int index)
{
	philo->index = index;
	philo->last_meal = data->start_time;
	philo->times_eaten = 0;
	philo->finished = false;
	philo->is_eating = false;
	philo->forks = &data->forks;
	philo->write_lock = &data->write_lock;
	philo->data = data;
}

void	init_monitor_thread(t_data *data, t_philo *philo)
{
	if (pthread_create(&philo->monitor, NULL, monitor_routine, philo))
		end(data, "Failed to create monitor thread.\n", 1, parent);
}

void	init_philosophers(t_data *data)
{
	int	i;

	data->philos = malloc(data->total_philos * sizeof(t_philo));
	if (!data->philos)
		end(data, "Memory allocation failed.\n", 1, parent);
	i = 0;
	while (i < data->total_philos)
	{
		init_philo_struct(data, &data->philos[i], i + 1);
		data->philos[i].pid = fork();
		if (data->philos[i].pid == 0)
		{
			init_monitor_thread(data, &data->philos[i]);
			philo_routine(data, &data->philos[i]);
			pthread_join(data->philos[i].monitor, NULL);
			end(data, NULL, 0, child);
		}
		i++;
	}
}
/* for testing:
void	print_sem(t_data *data, t_sem *sem)
{
	int	temp;

	temp = -1;
	sem_getvalue(sem->ptr, &temp);
	if (data)
		printf("\n%s: %i\n", sem->name, temp);
}
*/
