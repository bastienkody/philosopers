/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:22:51 by bguillau          #+#    #+#             */
/*   Updated: 2023/05/05 16:28:58 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*	libraries	*/
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

/*	state const	*/
# define EAT 0
# define SLEEP 1
# define THINK 2
# define DEAD 3

/*	msg const	*/
# define F "has taken a fork"
# define E "is eating"
# define S "is sleeping"
# define T "is thinking"
# define D "died"

/*	for bool	*/
typedef int	t_bool;
# define TRUE 1
# define FALSE 0

/*	typedef	*/
typedef struct s_data
{
	struct timeval	t0;
	int				nb_philo;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				tt_think;
	int				min_meals;
	t_bool			go_on;
	pthread_mutex_t	**futex;
	pthread_mutex_t	*wutex;
}			t_data;

typedef struct s_philo
{
	int					nb;
	int					state;
	unsigned long int	t_id;
	unsigned long int	last_meal;
	int					meal_nb;
	t_data				*data;
}			t_philo;

/*	inits	*/
t_data					*arg_to_data(int argc, char **argv);
t_philo					**init_philo(t_data *data);

/*	free	*/
void					free_philo(t_philo **philo);
void					free_futex(pthread_mutex_t **futex);
void					end_free(t_philo **philo, t_data *data);
void					phcreate_failure_mgmt(t_philo **philo, int i);

/*	threading	*/
void					launcher(t_philo **philo);

/*	actions	*/
void					eatp(t_philo *philo);
void					sleepp(t_philo *philo);
void					thinkp(t_philo *philo);

/*	utils	*/
int						ft_atoi_noverflw(const char *nptr);

/*	time	*/
void					ft_usleep(unsigned int usec);
unsigned long int		c_time(struct timeval t0);

/*	printer	*/
void					ft_printer(unsigned long int time, int philo_nb,
							char *msg, pthread_mutex_t *wutex);

/*	print-debug	*/
void					print_data(t_data *data);
void					print_philo(t_philo **philo);
void					print_futex(pthread_mutex_t **futex);

#endif
