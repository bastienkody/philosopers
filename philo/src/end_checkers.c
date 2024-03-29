/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_checkers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:41:18 by bguillau          #+#    #+#             */
/*   Updated: 2023/09/13 14:41:20 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	turn_go_on_to_false(t_philo *philo)
{
	pthread_mutex_lock(philo->data->gutex);
	philo->data->go_on = FALSE; 
	pthread_mutex_unlock(philo->data->gutex);
}

/*	ALL CHECKERS :	ret 1 = go_on;	ret 0 = end	*/

int	check_go_on(t_philo *philo)
{
	pthread_mutex_lock(philo->data->gutex);
	if (!philo->data->go_on)
		return (pthread_mutex_unlock(philo->data->gutex), 0);
	return (pthread_mutex_unlock(philo->data->gutex), 1);
}

int	check_death(t_philo **philo)
{
	int	i;

	i = -1;
	while (philo[++i])
	{
		pthread_mutex_lock((*philo)->data->mealtex);
		if (c_time(philo[i]->data->t0) - (philo[i]->last_meal) > \
			(unsigned long)philo[i]->data->tt_die * 1000)
		{
			pthread_mutex_unlock((*philo)->data->mealtex);
			turn_go_on_to_false(philo[i]);
			ft_printer(c_time(philo[i]->data->t0), philo[i]->nb, D, \
				philo[i]->data->wutex);
			return (0);
		}
		pthread_mutex_unlock((*philo)->data->mealtex);
	}
	return (1);
}

/*	only called if meal_nb specified in argv	*/
int	check_meal(t_philo **philo)
{
	int	i;

	i = -1;
	pthread_mutex_lock((*philo)->data->mealtex);
	while (philo[++i])
		if (philo[i]->meal_nb > 0)
			return (pthread_mutex_unlock((*philo)->data->mealtex), 1);
	pthread_mutex_unlock((*philo)->data->mealtex);
	turn_go_on_to_false(philo[0]);
	return (0);
}
