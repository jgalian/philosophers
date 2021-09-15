#include "philo.h"

void	start_threads(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->n_philos)
		pthread_create(&args->philos->tid, NULL, &routine, &args->philos[i]);
	i = -1;
	while (++i < args->n_philos)
		pthread_join(args->philos->tid, NULL);
}

void	*routine(void *struc)
{
	t_philo 	*philo;
	//uint64_t	timestamp;

 	philo = struc;
	philo->time_to_live = get_time(philo->parent) + philo->parent->time_to_die;
	while (philo->parent->philo_died == FALSE
	 && philo->time_to_live > (get_time(philo->parent))
	 &&	(philo->parent->times_must_eat == 0
	 || philo->parent->n_philos_done_eaten < philo->parent->n_philos))
	{
		if (philo->parent->n_philos > 1 && grab_forks(philo) == TRUE)
			try_to_eat(philo);
	}
	if (philo->parent->philo_died == FALSE && (philo->parent->times_must_eat == 0
	 || philo->parent->n_philos_done_eaten < philo->parent->n_philos))
	 	philo_died(philo);
	//printf("%ld  %i sale------> died:%i eaten:%i\n", (timestamp = get_time(philo->parent) - philo->parent->start_time), philo->pos, philo->parent->philo_died, philo->parent->n_philos_done_eaten);
	return (0);
}

unsigned short	grab_forks(t_philo *philo)
{
	//print_status(philo, "is trying to take the forks\n");
	pthread_mutex_lock(philo->m_r_fork);
	pthread_mutex_lock(philo->m_l_fork);
	if (*(philo)->r_fork == DOWN && *(philo)->l_fork == DOWN)
	{
		*(philo)->r_fork = UP;
		print_status(philo, "has taken l_fork\n");
		*(philo)->l_fork = UP;
		print_status(philo, "has taken r_fork\n");
	}
	else
	{
		pthread_mutex_unlock(philo->m_r_fork);
		pthread_mutex_unlock(philo->m_l_fork);
		return (FALSE);
	}
	pthread_mutex_unlock(philo->m_r_fork);
	pthread_mutex_unlock(philo->m_l_fork);
	return (TRUE);
}

void	try_to_eat(t_philo *philo)
{
	philo->times_has_eaten++;
	if (philo->times_has_eaten == philo->parent->times_must_eat)
	{
		pthread_mutex_lock(philo->parent->m_done_eaten);
		philo->parent->n_philos_done_eaten++;
		pthread_mutex_unlock(philo->parent->m_done_eaten);
	}
	print_status(philo, "is eating\n");
	philo->time_to_live = get_time(philo->parent) + philo->parent->time_to_die;
	doing_something(philo->parent, philo->parent->time_to_eat);
	// *(philo)->r_fork = DOWN;
	// *(philo)->l_fork = DOWN;
	philo_sleep(philo);
}

void	philo_died(t_philo *philo)
{
	//printf("%i entra en la funcion philo_died()\n", philo->pos);
	print_status(philo, "died\n");
	pthread_mutex_lock(philo->parent->m_philo_died);
	philo->parent->philo_died = TRUE;
	pthread_mutex_unlock(philo->parent->m_philo_died);
	//print_status(philo, "died\n");
}

void	philo_sleep(t_philo *philo)
{
	if (get_time(philo->parent) + philo->parent->time_to_sleep < philo->time_to_live)
	{
		print_status(philo, "is sleeping\n");
		*(philo)->r_fork = DOWN;
		*(philo)->l_fork = DOWN;
		doing_something(philo->parent, philo->parent->time_to_sleep);
		print_status(philo, "is thinking\n");
		usleep(10);
	}
	else
	{
		doing_something(philo->parent, philo->time_to_live - get_time(philo->parent));
		philo_died(philo);
	}
}

void	doing_something(t_args *args, uint64_t msec)
{
	uint64_t	time_to_stop;

	time_to_stop = get_time(args) + msec;
	while (get_time(args) < time_to_stop)
		usleep(500);
}
