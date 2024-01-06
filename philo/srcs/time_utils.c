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

#include "philo.h"

/*
int gettimeofday(struct timeval *restrict tv,
                        struct timezone *_Nullable restrict tz);
The tv argument is a struct timeval (as specified in <sys/time.h>):
	struct timeval
	{
		time_t		tv_sec;		// seconds
		suseconds_t	tv_usec;	// microseconds
	};
convert tv_sec and tv_usec to milliseconds
*/
size_t	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(size_t duration)
{
	size_t	start_time;

	start_time = current_time();
	while ((current_time() - start_time) < duration)
		usleep(500);
}
