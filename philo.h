#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <sys/time.h>
#include <string.h>

#define	UP 1
#define	DOWN 0
#define	TRUE 1
#define	FALSE 0

typedef struct		s_philo
{
	unsigned short	pos;
	unsigned short	times_has_eaten;
	uint64_t		time_to_live;
	struct s_args 	*parent;
	pthread_t 		tid;
	unsigned short	*r_fork;
	unsigned short	*l_fork;
	pthread_mutex_t	*m_r_fork;
	pthread_mutex_t	*m_l_fork;
}					t_philo;

typedef struct		s_args
{
	unsigned short	n_philos;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	unsigned short	times_must_eat;
	uint64_t		start_time;
	unsigned short	philo_died;
	unsigned short	n_philos_done_eaten;
	t_philo			*philos;
	unsigned short	*forks;
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	*m_philo_died;
	pthread_mutex_t	*m_done_eaten;
	pthread_mutex_t	*m_print_status;

}					t_args;

/*
* philo.c
*/
void	destroy_mutex(t_args *args);
void	exit_program(t_args *args, unsigned short num);

/*
* setup.c
*/
void	check_argument_errors(int argc, char *argv[]);
t_args	*setup_args_struct(char *argv[]);
void	alloc_memory(t_args *args);
void	setup_philos_struct(t_args *args);
void	init_mutex(t_args *args);


/*
* threads.c
*/
void			start_threads(t_args *args);
void			*routine(void *struc);
unsigned short	grab_forks(t_philo *philo);
void			try_to_eat(t_philo *philo);
void			philo_died(t_philo *philo);
void			philo_sleep(t_philo *philo);
void			doing_something(t_args *args, uint64_t msec);

/*
* utils.c
*/
int			ft_atoi(const char *str);
_Bool		ft_isdigit(int c);
void		print_error(t_args *args, char *error_msg);
void		print_status(t_philo *philo, char *message);
uint64_t	get_time(t_args *args);

