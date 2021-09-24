/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalian- <jgalian-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 11:45:54 by jgalian-          #+#    #+#             */
/*   Updated: 2021/09/24 12:49:44 by jgalian-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_args		*args;

	if (check_argument_errors(argc, argv) == -1)
		return (-1);
	args = malloc(sizeof(t_args));
	if (!args)
	{
		printf("Error during memory allocation\n");
		return (-1);
	}
	if (setup_args_struct(argv, args) == -1)
		return (-1);
	if (setup_philos_struct(args) == -1)
		return (-1);
	if (start_threads(args) == -1)
		return (-1);
	exit_program(args);
	return (0);
}

void	exit_program(t_args *args)
{
	short	i;

	i = -1;
	printf("entra");
	while (++i < args->n_philos)
		pthread_mutex_destroy(&args->philos->fork);
	pthread_mutex_destroy(&args->m_print);
	pthread_mutex_destroy(&args->m_done_eating);
	pthread_mutex_destroy(&args->m_pos);
	if (args->philos != NULL)
		free(args->philos);
	if (args != NULL)
		free(args);
}
