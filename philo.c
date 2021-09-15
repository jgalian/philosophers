#include "philo.h"

int main(int argc, char *argv[])
{
	t_args	*args;

	check_argument_errors(argc, argv);
	args = setup_args_struct(argv);
	alloc_memory(args);
	setup_philos_struct(args);
	init_mutex(args);
	start_threads(args);
	destroy_mutex(args);
	exit_program(args, 0);
	return (0);
}

void	destroy_mutex(t_args *args)
{
	short	i;

	i = -1;
	while (++i < args->n_philos)
		pthread_mutex_destroy(args->philos->m_r_fork);
	pthread_mutex_destroy(args->m_philo_died);
	pthread_mutex_destroy(args->m_done_eaten);
	pthread_mutex_destroy(args->m_print_status);
}

void	exit_program(t_args *args, unsigned short num)
{
	if (args->times_must_eat > 0 && args->n_philos_done_eaten == args->n_philos)
		printf("\nAll philosophers are done eating\n\n");
	if (args->m_philo_died != NULL)
		free(args->m_philo_died);
	if (args->m_done_eaten != NULL)
		free(args->m_done_eaten);
	if (args->m_print_status != NULL)
		free(args->m_print_status);
	if (args->m_forks != NULL)
		free(args->m_forks);
	if (args->forks != NULL)
		free(args->forks);
	if (args->philos != NULL)
		free(args->philos);
	if (args != NULL)
		free(args);
	exit(num);
}

