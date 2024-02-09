/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycostode <ycostode@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:15:57 by ycostode          #+#    #+#             */
/*   Updated: 2024/02/08 16:39:58 by ycostode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef unsigned long long	t_time;
typedef enum e_state
{
	THINKING,
	HAS_FORK,
	HAS_EATEN,
	HAS_SLEPT,
	DEAD,
}							t_state;
typedef struct s_info
{
	t_time					die_time;
	t_time					eat_time;
	t_time					sleep_time;
	int						meals;
}							t_info;
typedef struct s_bool_mutex
{
	bool					value;
	pthread_mutex_t			mutex;
}							t_bool_mutex;
typedef struct s_state_mutex
{
	t_state					value;
	pthread_mutex_t			mutex;
}							t_state_mutex;
typedef struct s_program	t_program;
typedef struct s_person
{
	int						id;
	int						meals;
	pthread_t				thread;
	t_state_mutex			state;
	t_bool_mutex			fork;
	t_bool_mutex			*spare_fork;
	t_program				*program;
	struct timeval			last_meal;
}							t_person;
typedef struct s_program
{
	struct timeval			time;
	int						number;
	t_person				*persons;
	t_info					info;
}							t_program;

void						die(t_person *person);
bool						is_dead(t_program program);
bool						enough_meal(t_person person);
void						daily_sleep(t_person *person);
void						daily_eat(t_person *person);
bool						atoi_convert(const char *s, int *n);
bool						atot_convert(const char *s, t_time *n);
t_time						compare_current_time(struct timeval time);
t_time						current_time(t_program program);
void						take_fork(t_person *person);
bool						check_state(t_person person, t_state state);
void						set_state(t_person *person, t_state state);

#endif
