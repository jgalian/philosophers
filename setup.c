/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalian- <jgalian-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 11:45:48 by jgalian-          #+#    #+#             */
/*   Updated: 2021/09/24 13:10:59 by jgalian-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

short	check_argument_errors(int argc, char *argv[])
{
	short	i;
	short	j;

	if (argc < 5 || argc > 6)
	{
		printf("This program needs 4 or 5 arguments to work\n");
		return (-1);
	}
	i = 0;
	while (++i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (ft_isdigit(argv[i][j]) == FALSE)
			{
				printf("Arguments should have only digits\n");
				return (-1);
			}
			j++;
		}
	}
	return (0);
}

short	setup_args_struct(char *argv[], t_args *args)
{
	long long int	num;
	long long int	die;
	long long int	eat;
	long long int	sleep;
	long long int	times;

	num = ft_atoi(argv[1]);
	die = ft_atoi(argv[2]);
	eat = ft_atoi(argv[3]);
	sleep = ft_atoi(argv[4]);
	if (argv[5])
		times = ft_atoi(argv[5]);
	else
		times = 0;
	if (num < 1 || num > 200 || die < 1 || eat < 1 || sleep < 1 || times < 0)
	{
		printf("Incorrect argument value\n");
		return (-1);
	}
	args->n_philos = (uint64_t)num;
	args->times_must_eat = (uint64_t)times;
	init_values_args_struct(args, die, eat, sleep);
	return (0);
}

void	init_values_args_struct(t_args *args, long long int die,
	long long int eat, long long int sleep)
{
	args->time_to_die = (uint64_t)die;
	args->time_to_eat = (uint64_t)eat;
	args->time_to_sleep = (uint64_t)sleep;
	args->start_time = get_time();
	args->is_done = 0;
	args->pos = 0;
	args->philos = NULL;
	pthread_mutex_init(&args->m_done_eating, NULL);
	pthread_mutex_init(&args->m_print, NULL);
	pthread_mutex_init(&args->m_pos, NULL);
}

short	setup_philos_struct(t_args *args)
{
	short	i;

	args->philos = malloc(sizeof(t_philo) * args->n_philos);
	if (!args->philos)
	{
		printf("Error during memory allocation\n");
		return (-1);
	}
	i = -1;
	while (++i < args->n_philos)
	{
		args->philos[i].times_has_eaten = 0;
		args->philos[i].time_last_meal = args->start_time;
		pthread_mutex_init(&args->philos[i].fork, NULL);
	}
	return (0);
}
