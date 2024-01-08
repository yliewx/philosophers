/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 17:39:14 by yliew             #+#    #+#             */
/*   Updated: 2023/12/27 17:39:27 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
int gettimeofday(struct timeval *restrict tv,
                        struct timezone *_Nullable restrict tz);
The tv argument is a struct timeval (as specified in <sys/time.h>):
           struct timeval {
               time_t      tv_sec;     // seconds
               suseconds_t tv_usec;    // microseconds
           };
convert tv_sec and tv_usec to milliseconds
*/
size_t	current_time(t_data *data)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		end(data, "Failed gettimeofday().\n", 1, child);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(size_t duration, t_data *data)
{
	size_t	start_time;

	start_time = current_time(data);
	while ((current_time(data) - start_time) < duration)
		usleep(500);
}
