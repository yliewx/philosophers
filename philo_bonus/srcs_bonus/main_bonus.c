/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 16:34:05 by yliew             #+#    #+#             */
/*   Updated: 2023/12/22 16:58:20 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
argv[1]: no. of philosophers (eval: do not test with >200)
argv[2]: time to die (ms)
argv[3]: time to eat (ms)
argv[4]: time to sleep (ms)
(2 to 4: eval: do not test with <60 ms)
argv[5]: (optional) no. of times each philosopher must eat
*/
void	init_data(t_data *data, int argc, char **argv)
{
	data->start_time = current_time(data);
	data->total_philos = ft_atoi_long(argv[1]);
	data->time_to_die = ft_atoi_long(argv[2]);
	data->time_to_eat = ft_atoi_long(argv[3]);
	data->time_to_sleep = ft_atoi_long(argv[4]);
	if (argc == 6)
		data->meal_quota = ft_atoi_long(argv[5]);
	else
		data->meal_quota = -1;
	data->philos = NULL;
}

void	verify_params(t_data *data, int argc, char **argv)
{
	check_numeric(data, argc, argv);
	if (data->total_philos > 200)
		end(data, "Philosophers should not exceed 200.\n", 1, parent);
	else if (data->total_philos < 1)
		end(data, "No philosophers found.\n", 1, parent);
	if (data->time_to_die < 60 || data->time_to_eat < 60
		|| data->time_to_sleep < 60)
		end(data, "Time values should not be <60 m/s.\n", 1, parent);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("Enter 5 or 6 arguments.\n");
		return (0);
	}
	init_data(&data, argc, argv);
	verify_params(&data, argc, argv);
	init_semaphores(&data);
	init_philosophers(&data);
	if (data.meal_quota > 0)
		wait_all_philos(&data);
	sem_wait(data.exit_lock.ptr);
	end(&data, NULL, 0, parent);
	return (0);
}
