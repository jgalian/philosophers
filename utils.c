#include "philo.h"

int		ft_atoi(const char *str)
{
	int			i;
	long int	sign;
	long int	result;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\r' || str[i] == '\n'
							|| str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + str[i] - '0';
		i++;
		if (sign * result > 2147483647)
			return (-1);
		else if (sign * result < -2147483648)
			return (0);
	}
	return (sign * result);
}

_Bool	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (TRUE);
	}
	return (FALSE);
}

void	print_error(t_args *args, char *error_msg)
{
	printf("%s", error_msg);
	exit_program (args, -1);
}

void	print_status(t_philo *philo, char *message)
{
	uint64_t	timestamp;

	if (philo->parent->philo_died == FALSE)
	{
		timestamp = get_time(philo->parent) - philo->parent->start_time;
		pthread_mutex_lock(philo->parent->m_print_status);
		printf("%ld  %i  %s", timestamp, philo->pos, message);
		pthread_mutex_unlock(philo->parent->m_print_status);
	}
}

uint64_t	get_time(t_args *args)			// devuelve el tiempo actual en ml segundos
{
	static struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		print_error(args, "Error using gettimeofday() function\n");
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
