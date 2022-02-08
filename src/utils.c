/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 13:10:43 by xuwang            #+#    #+#             */
/*   Updated: 2021/08/09 16:37:01 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	_free_(void *philo)
{
	if (philo)
		free(philo);
	philo = NULL;
}

int	__exit__(char *msg, t_each_philo *each_philo, t_philo *philo, int ret)
{
	if (msg)
		printf("%s\n", msg);
	if (philo)
	{
		if (philo->fork)
			_free_(philo->fork);
	}
	if (each_philo)
	{
		if (each_philo->info_utils)
			_free_(each_philo->info_utils);
		_free_(each_philo);
	}
	return (ret);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(count * size);
	if (ptr)
		memset(ptr, 0, count * size);
	return (ptr);
}

long	ft_atoi(const char *str)
{
	int		signe;
	long	res;

	signe = 1;
	res = 0;
	while (*str && ((*str >= '\t' && *str <= '\r') || (*str == ' ')))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signe = -1;
		++str;
	}
	while (*str && (*str >= '0' && *str <= '9'))
	{
		res = res * 10 + *str - '0';
		++str;
	}
	return (res * signe);
}
