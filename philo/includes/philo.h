/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 16:34:20 by yliew             #+#    #+#             */
/*   Updated: 2023/12/22 17:00:13 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

/*status*/

# define GRAB_FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"
# define FINISHED "has finished eating"

/*text colour*/

# define BROWN "\033[1;33m"
# define LIGHT "\033[0;33m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define RESET "\033[0m"

typedef struct s_philo
{
	int				index;
	size_t			last_meal;
	int				times_eaten;
	bool			is_eating;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				total_philos;
	size_t			start_time;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				meal_quota;
	int				finished_count;
	int				dead_count;
	t_philo			*philos;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	char			*error;
}	t_data;

/*init.c*/
int		init_mutex(t_data *data);
int		init_philosophers(t_data *data);
int		init_threads(t_data *data, t_philo **philos);
int		join_threads(t_data *data);

/*routine.c*/
void	*philo_routine(void *phil);
void	*monitor_routine(void *program);
bool	loop_ended(t_data *data);
bool	all_finished(t_data *data);

/*actions.c*/
int		grab_fork(t_philo *philo);
int		drop_fork(t_philo *philo);
int		go_eat(t_philo *philo);
int		go_sleep(t_philo *philo);
int		go_think(t_philo *philo);

/*time_utils.c*/
size_t	current_time(void);
void	ft_usleep(size_t duration);

/*exit_message_utils.c*/
void	print_status(t_philo *philo, char *status);
void	print_msg(char *message, int fd);
void	end(t_data *data, char *message);
void	detach_threads(t_data *data);
void	destroy_mutex(t_data *data);

/*string_utils.c*/
int		check_numeric(int argc, char **argv);
size_t	ft_atoi_long(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
