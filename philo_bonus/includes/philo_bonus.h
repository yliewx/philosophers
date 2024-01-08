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

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <errno.h>

/*status*/

# define GRAB_FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"
# define FINISHED "has finished eating"

/*semaphores*/

# define SEM_FORKS "/forks"
# define SEM_WRITE "/write"
# define SEM_DEAD "/dead"
# define SEM_EXIT "/exit"

/*text colour*/

# define BROWN "\033[1;33m"
# define LIGHT "\033[0;33m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define RESET "\033[0m"

typedef struct s_sem
{
	sem_t		*ptr;
	char		*name;
}	t_sem;

typedef struct s_philo
{
	pid_t			pid;
	int				index;
	size_t			last_meal;
	int				times_eaten;
	bool			finished;
	bool			is_eating;
	pthread_t		monitor;
	t_sem			*forks;
	t_sem			*write_lock;
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
	t_philo			*philos;
	t_sem			forks;
	t_sem			write_lock;
	t_sem			dead_lock;
	t_sem			exit_lock;
}	t_data;

enum e_process
{
	parent,
	child,
};

/*init.c*/
void	create_sem(t_data *data, t_sem *sem, char *name, int value);
void	init_semaphores(t_data *data);
void	init_philosophers(t_data *data);

/*routine.c*/
void	*philo_routine(t_data *data, t_philo *philo);
void	*monitor_routine(void *process);
bool	loop_ended(t_data *data);
bool	is_dead(t_data *data, t_philo *philo);

/*actions.c*/
int		grab_fork(t_philo *philo);
int		drop_fork(t_philo *philo);
int		go_eat(t_philo *philo);
int		go_sleep(t_philo *philo);
int		go_think(t_philo *philo);

/*time_utils.c*/
size_t	current_time(t_data *data);
void	ft_usleep(size_t duration, t_data *data);

/*message_utils.c*/
void	print_status(t_philo *philo, char *status);
void	print_msg(char *message, int fd);

/*exit_utils.c*/
void	end(t_data *data, char *message, int exit_code, int process);
void	close_semaphores(t_data *data);
void	unlink_semaphores(void);
void	wait_all_philos(t_data *data);

/*string_utils.c*/
void	check_numeric(t_data *data, int argc, char **argv);
size_t	ft_atoi_long(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);

#endif
