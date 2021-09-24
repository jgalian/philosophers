/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalian- <jgalian-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 11:46:49 by jgalian-          #+#    #+#             */
/*   Updated: 2021/09/24 13:10:36 by jgalian-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdint.h>
# include <sys/time.h>
# include <string.h>

# define TRUE 1
# define FALSE 0

typedef struct s_philo
{
	unsigned short	times_has_eaten;
	uint64_t		time_last_meal;
	pthread_t		tid;
	pthread_mutex_t	fork;
}					t_philo;

typedef struct s_args
{
	unsigned short	n_philos;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	unsigned short	times_must_eat;
	uint64_t		start_time;
	unsigned short	is_done;
	unsigned short	pos;
	t_philo			*philos;
	pthread_t		control_tid;
	pthread_mutex_t	m_done_eating;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_pos;
}					t_args;

/*
* philo.c
*/
void		exit_program(t_args *args);

/*
* setup.c
*/
short		check_argument_errors(int argc, char *argv[]);
short		setup_args_struct(char *argv[], t_args *args);
void		init_values_args_struct(t_args *args, long long int die,
				long long int eat, long long int sleep);
short		setup_philos_struct(t_args *args);

/*
* threads.c
*/
short		start_threads(t_args *args);
void		*philo_routine(void *struc);
void		*control_routine(void *struc);
void		philo_eat(t_args *args, unsigned short pos, unsigned short next);
void		doing_something(uint64_t msec);

/*
* utils.c
*/
int			ft_atoi(const char *str);
_Bool		ft_isdigit(int c);
void		print_status(t_args *args, unsigned short pos, char *message);
uint64_t	get_time(void);

#endif
