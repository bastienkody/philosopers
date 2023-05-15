/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:58:53 by bguillau          #+#    #+#             */
/*   Updated: 2023/05/08 19:58:56 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/* do not execute if philo->t_id == 0 (means pb with thread create) */
void	*do_smthg(void * t)
{
	printf("salut from philo %i\n", *(int *)t);
	return (NULL);
}

/*	create a thread per philo + assigns th_id
	if create fails : detach philo and return (no join)
	pb : launcher returns to main before all detached thread finished
	->add	*/
void	launcher(t_philo **philo)
{
	pthread_t	thread;
	int			i;

	i = -1;
	while (philo[++i])
	{
		if (pthread_create(&thread, NULL, &do_smthg, &philo[i]->nb))
			return (phcreate_failure_mgmt(philo, i + 1), (void) 0);
		else
			philo[i]->t_id = thread;
	}
	i = -1;
	while (philo[++i])
	{
		if (pthread_join(philo[i]->t_id, NULL))
			printf("pb joining t_id %luWhat can i do??\n", philo[i]->t_id);
		else
			printf("joined t_id %lu\n", philo[i]->t_id);
	}
	return (printf("launcher returned\n"), (void) 0);
}
 