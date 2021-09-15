#include "philo.h"

void	check_argument_errors(int argc, char *argv[])
{
	short	i;
	short	j;

	if (argc < 5 || argc > 6)
	{
		printf("This program needs 4 or 5 arguments to work\n");
		exit(-1);
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
				exit(-1);
			}
			j++;
		}
	}
}

t_args	*setup_args_struct(char *argv[])
{
	t_args	*ret;

	ret = malloc(sizeof(t_args));
	if (!ret)
	{
		printf("Error during memory allocation\n");
		exit(-1);
	}
	ret->n_philos = ft_atoi(argv[1]);
	ret->time_to_die = ft_atoi(argv[2]); // en ml segundos
	ret->time_to_eat = ft_atoi(argv[3]);
	ret->time_to_sleep = ft_atoi(argv[4]);
	ret->times_must_eat = 0;
	if (argv[5])
		ret->times_must_eat = ft_atoi(argv[5]);
	ret->start_time = get_time(ret);
	ret->philo_died = FALSE;
	ret->n_philos_done_eaten = FALSE;
	ret->philos = NULL;
	ret->forks = NULL;
	ret->m_forks = NULL;
	ret->m_philo_died = NULL;
	ret->m_print_status = NULL;
	return (ret);
}

void	alloc_memory(t_args *args)
{

	args->philos = malloc(sizeof(t_philo) * args->n_philos);
	args->forks = malloc(sizeof(unsigned short) * args->n_philos);
	args->m_forks = malloc(sizeof(pthread_mutex_t) * args->n_philos);
	args->m_philo_died = malloc(sizeof(pthread_mutex_t));
	args->m_done_eaten = malloc(sizeof(pthread_mutex_t));
	args->m_print_status = malloc(sizeof(pthread_mutex_t));
	if (!args->philos || !args->forks || !args->m_forks || !args->m_philo_died || !args->m_done_eaten || !args->m_print_status)
		print_error(args, "Error during memory allocation\n");
}

void	setup_philos_struct(t_args *args)
{
	short	i;

	i = -1;
	while (++i < args->n_philos)
	{
		args->philos[i].pos = i + 1;
		args->philos[i].parent = args;
		args->philos[i].times_has_eaten = 0;
		args->philos[i].r_fork = &args->forks[i];
		if (i == 0)
			args->philos[i].l_fork = &args->forks[args->n_philos - 1];
		else
			args->philos[i].l_fork = &args->forks[i - 1];
		args->philos[i].m_r_fork = &args->m_forks[i];
		if (i == 0)
			args->philos[i].m_l_fork = &args->m_forks[args->n_philos - 1];
		else
			args->philos[i].m_l_fork = &args->m_forks[i - 1];
		*(args)->philos[i].r_fork = DOWN;
		*(args)->philos[i].l_fork = DOWN;
	}
}

void	init_mutex(t_args *args)
{
	short	i;

	i = -1;
	while (++i < args->n_philos)
	{
		pthread_mutex_init(args->philos[i].m_r_fork, NULL);
		pthread_mutex_init(args->philos[i].m_l_fork, NULL);
	}
	pthread_mutex_init(args->m_philo_died, NULL);
	pthread_mutex_init(args->m_done_eaten, NULL);
	pthread_mutex_init(args->m_print_status, NULL);
}

