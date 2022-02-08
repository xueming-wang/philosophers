/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 13:10:49 by xuwang            #+#    #+#             */
/*   Updated: 2021/08/09 17:52:13 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	creat_pthread(t_philo *philo, t_each_philo *each_philo)
{
	int	i;

	i = 0;
	while (i < philo->nbr_philo)
	{
		if (pthread_mutex_init(&philo->fork[i++], NULL) != 0)
			return (FAILURE);
	}
	if (pthread_mutex_init(&philo->mutex, NULL) != 0)
		return (FAILURE);
	i = 0;
	while (i < philo->nbr_philo)
	{
		each_philo[i].info_utils = philo;
		if (pthread_create(&(each_philo[i].philo),
				NULL, do_philo, (void *)&(each_philo[i])) != 0)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

static int	run_pthread(t_philo *philo, t_each_philo *each_philo)
{
	int	i;

	if (creat_pthread(philo, each_philo) != SUCCESS)
		return (FAILURE);
	i = 0;
	while (i < philo->nbr_philo)
	{
		if (pthread_join(each_philo[i++].philo, NULL) != 0)
			return (FAILURE);
	}
	i = 0;
	while (i < philo->nbr_philo)
		pthread_mutex_destroy(&philo->fork[i++]);
	pthread_mutex_destroy(&philo->mutex);
	return (SUCCESS);
}

static int	check_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_atoi(av[i]) > INT32_MAX)
				return (FAILURE);
			if (av[i][0] == '-')
				return (FAILURE);
			if (av[i][0] == '0' && av[i][1] == '\0')
				return (FAILURE);
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return (FAILURE);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_each_philo	*each_philo;
	t_philo			*philo_info;

	if (ac > 6 || ac < 5)
		return (__exit__("Args Error", NULL, NULL, FAILURE));
	if (check_args(av) == FAILURE)
		return (__exit__("Args Error", NULL, NULL, FAILURE));
	each_philo = init_each_philo(ft_atoi(av[1]));
	if (!each_philo)
		return (__exit__("Init Error", each_philo, NULL, FAILURE));
	philo_info = init_value(av);
	if (!philo_info)
		return (__exit__("Init Error", each_philo, philo_info, FAILURE));
	philo_info->start_time = get_time();
	if (philo_info->start_time == -1)
		return (__exit__("Time Error", each_philo, philo_info, FAILURE));
	if (run_pthread(philo_info, each_philo) == FAILURE)
		return (__exit__("Pthread Error", each_philo, philo_info, FAILURE));
	return (__exit__(NULL, each_philo, philo_info, SUCCESS));
}
