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

#include "philo.h"

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
	data->start_time = current_time();
	data->total_philos = ft_atoi_long(argv[1]);
	data->time_to_die = ft_atoi_long(argv[2]);
	data->time_to_eat = ft_atoi_long(argv[3]);
	data->time_to_sleep = ft_atoi_long(argv[4]);
	if (argc == 6)
		data->meal_quota = ft_atoi_long(argv[5]);
	else
		data->meal_quota = -1;
	data->finished_count = 0;
	data->dead_count = 0;
	data->philos = NULL;
	data->error = NULL;
}

int	verify_params(t_data *data, int argc, char **argv)
{
	init_data(data, argc, argv);
	if (!check_numeric(argc, argv))
	{
		data->error = "Error: Non-numeric or negative argument.\n";
		return (0);
	}
	if (data->total_philos > 200)
	{
		data->error = "Error: Philosophers should not exceed 200.\n";
		return (0);
	}
	else if (data->total_philos < 1)
	{
		data->error = "Error: No philosophers.\n";
		return (0);
	}
	if (data->time_to_die < 60 || data->time_to_eat < 60
		|| data->time_to_sleep < 60)
	{
		data->error = "Error: Time values should not be <60 m/s.\n";
		return (0);
	}
	return (1);
}

int	init_simulation(t_data *data)
{
	if (init_mutex(data)
		&& init_philosophers(data)
		&& init_threads(data, &data->philos)
		&& join_threads(data))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("Enter 5 or 6 arguments.\n");
		return (0);
	}
	if (verify_params(&data, argc, argv))
		init_simulation(&data);
	end(&data, data.error);
	return (0);
}
