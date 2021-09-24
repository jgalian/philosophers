/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalian- <jgalian-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 11:46:42 by jgalian-          #+#    #+#             */
/*   Updated: 2021/09/24 13:31:11 by jgalian-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

short	start_threads(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->n_philos)
	{
		if (pthread_create(&args->philos->tid, NULL, &philo_routine, args) != 0)
		{
			printf("Error creating a thread\n");
			return (-1);
		}
	}
	if (pthread_create(&args->control_tid, NULL, &control_routine, args) != 0)
	{
		printf("Error creating a thread\n");
		return (-1);
	}
	pthread_join(args->control_tid, NULL);
	return (0);
}

void	*philo_routine(void *struc)
{
	t_args			*args;
	unsigned short	pos;
	unsigned short	next;

	args = struc;
	pthread_mutex_lock(&args->m_pos);
	pos = args->pos++;
	pthread_mutex_unlock(&args->m_pos);
	if (pos == args->n_philos - 1)
		next = 0;
	else
		next = pos + 1;
	if (pos % 2 != 0)
		doing_something(args->time_to_eat);
	while (1)
	{
		philo_eat(args, pos, next);
		print_status(args, pos, "is sleeping\n");
		doing_something(args->time_to_sleep);
		print_status(args, pos, "is thinking\n");
	}
	return (0);
}

void	philo_eat(t_args *args, unsigned short pos, unsigned short next)
{
	pthread_mutex_lock(&args->philos[pos].fork);
	print_status(args, pos, "has taken a fork\n");
	pthread_mutex_lock(&args->philos[next].fork);
	print_status(args, pos, "has taken a fork\n");
	print_status(args, pos, "is eating\n");
	args->philos[pos].time_last_meal = get_time();
	doing_something(args->time_to_eat);
	if (++args->philos[pos].times_has_eaten == args->times_must_eat)
	{
		pthread_mutex_lock(&args->m_done_eating);
		args->is_done++;
		pthread_mutex_unlock(&args->m_done_eating);
	}
	pthread_mutex_unlock(&args->philos[pos].fork);
	pthread_mutex_unlock(&args->philos[next].fork);
}

void	doing_something(uint64_t msec)
{
	uint64_t	time_to_stop;

	time_to_stop = get_time() + msec;
	while (get_time() < time_to_stop)
		usleep(60);
}

void	*control_routine(void *struc)
{
	t_args		*args;
	short		i;
	short		loop_control;

	args = struc;
	loop_control = TRUE;
	while (loop_control == TRUE)
	{
		i = -1;
		while (++i < args->n_philos)
		{
			if (get_time() > args->philos[i].time_last_meal + args->time_to_die
				|| (args->times_must_eat != 0 && args->is_done == args->n_philos))
			{
				pthread_mutex_lock(&args->m_print);
				if (args->times_must_eat != 0 && args->is_done == args->n_philos)
					printf("%s", "all philosophers are done\n");
				else
					printf("%lld  %i  %s", get_time() - args->start_time,
						i + 1, "died\n");
				loop_control = FALSE;
				break ;
			}
		}
	}
	return (0);
}
