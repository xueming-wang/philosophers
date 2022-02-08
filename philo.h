/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 13:10:55 by xuwang            #+#    #+#             */
/*   Updated: 2021/08/09 15:50:22 by xuwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <stdint.h>

# define FAILURE 1
# define SUCCESS 0
# define MICRO_SECOND 400

typedef struct s_each_philo
{
	pthread_t		philo;
	int				id;
	int				nbr_eat;
	long long		last_meal;
	struct s_philo	*info_utils;
}		t_each_philo;

typedef struct s_philo
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_philo_must_eat;
	long long		start_time;
	int				check_died;
	pthread_mutex_t	*fork;
	pthread_mutex_t	mutex;
}		t_philo;

long			ft_atoi(const char *str);
int				main(int ac, char **av);
t_philo			*init_value(char **av);
t_each_philo	*init_each_philo(int philo_nbr);
int				__exit__(char *msg, t_each_philo *each_philo,
					t_philo *philo, int ret);
void			*ft_calloc(size_t count, size_t size);
long long		get_time(void);
void			philo_state(t_each_philo *each_philo, int state);
void			*do_philo(void *each_philo);
void			ft_usleep(long long ms, t_each_philo *each_philo);
int				check_died(t_each_philo *each_philo);
int				check_enough_eat(t_each_philo *each_philo);

#endif
