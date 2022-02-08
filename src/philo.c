/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 14:08:00 by xuwang            #+#    #+#             */
/*   Updated: 2021/08/09 16:36:13 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_eat(t_each_philo *each_philo)
{
	const int	left = each_philo->id - 1;
	const int	right = each_philo->id % each_philo->info_utils->nbr_philo;

	if ((each_philo->id - 1) % 2 == 0)
	{
		if (each_philo->info_utils->nbr_philo != 1)
		{
			pthread_mutex_lock(&each_philo->info_utils->fork[right]);
			philo_state(each_philo, 1);
		}
		pthread_mutex_lock(&each_philo->info_utils->fork[left]);
		philo_state(each_philo, 1);
	}
	else
	{
		pthread_mutex_lock(&each_philo->info_utils->fork[left]);
		philo_state(each_philo, 1);
		pthread_mutex_lock(&each_philo->info_utils->fork[right]);
		philo_state(each_philo, 1);
	}
}

static void	putdown_fork(t_each_philo *each_philo)
{
	const int	left = each_philo->id - 1;
	const int	right = each_philo->id % each_philo->info_utils->nbr_philo;

	if ((each_philo->id - 1) % 2 == 0)
	{
		pthread_mutex_unlock(&each_philo->info_utils->fork[left]);
		pthread_mutex_unlock(&each_philo->info_utils->fork[right]);
	}
	else
	{
		pthread_mutex_unlock(&each_philo->info_utils->fork[right]);
		pthread_mutex_unlock(&each_philo->info_utils->fork[left]);
	}
}

static void	eating(t_each_philo *each_philo)
{
	if (each_philo->info_utils->nbr_philo != 1)
		philo_state(each_philo, 0);
	each_philo->last_meal = get_time();
	if (each_philo->info_utils->nbr_philo == 1)
		ft_usleep(each_philo->info_utils->time_to_die, each_philo);
	else
	{
		ft_usleep(each_philo->info_utils->time_to_eat, each_philo);
		each_philo->nbr_eat++;
	}
}

static void	sleeping(t_each_philo *each_philo)
{
	if (each_philo->info_utils->nbr_philo != 1)
		philo_state(each_philo, 2);
	ft_usleep(each_philo->info_utils->time_to_sleep, each_philo);
}

void	*do_philo(void *each_philo)
{
	while (check_died(each_philo) && !(check_enough_eat(each_philo)))
	{
		philo_eat((t_each_philo *)each_philo);
		eating((t_each_philo *)each_philo);
		putdown_fork((t_each_philo *)each_philo);
		sleeping(each_philo);
		if (((t_each_philo *)each_philo)->info_utils->nbr_philo != 1)
			philo_state(each_philo, 3);
		ft_usleep (((t_each_philo *)each_philo)->info_utils->time_to_eat
			- ((t_each_philo *)each_philo)->info_utils->time_to_sleep,
			each_philo);
	}
	return (NULL);
}
