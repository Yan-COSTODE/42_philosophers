/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycostode <ycostode@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:32:39 by ycostode          #+#    #+#             */
/*   Updated: 2024/02/08 16:40:18 by ycostode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_spare_fork(bool *fork, t_person *person)
{
	int	id;

	id = (person->id + 1) % person->program->number;
	person->spare_fork = &person->program->persons[id].fork;
	pthread_mutex_lock(&person->spare_fork->mutex);
	*fork = *fork && person->spare_fork->value;
	if (*fork)
	{
		person->spare_fork->value = false;
		printf("\033[1;37m%llu \033[1;30m%d has taken a fork\n\033[0m",
			current_time(*person->program), person->id + 1);
	}
	pthread_mutex_unlock(&person->spare_fork->mutex);
}

static void	take_my_fork(bool *fork, t_person *person)
{
	pthread_mutex_lock(&person->fork.mutex);
	if (person->fork.value)
	{
		person->fork.value = false;
		*fork = true;
	}
	else
		*fork = false;
	pthread_mutex_unlock(&person->fork.mutex);
}

void	take_fork(t_person *person)
{
	bool	fork;

	if (person->program->number == 1 || (person->program->number % 2 == 1
			&& compare_current_time(person->last_meal)
			< (person->program->info.eat_time * 3) && person->meals != 0))
		return ;
	take_my_fork(&fork, person);
	if (fork)
	{
		take_spare_fork(&fork, person);
		if (fork)
		{
			set_state(person, HAS_FORK);
			printf("\033[1;37m%llu \033[1;32m%d is eating\n\033[0m",
				current_time(*person->program), person->id + 1);
			gettimeofday(&person->last_meal, NULL);
		}
		else
		{
			pthread_mutex_lock(&person->fork.mutex);
			person->fork.value = true;
			pthread_mutex_unlock(&person->fork.mutex);
		}
	}
}

bool	check_state(t_person person, t_state state)
{
	bool	value;

	pthread_mutex_lock(&person.state.mutex);
	value = person.state.value == state;
	pthread_mutex_unlock(&person.state.mutex);
	return (value);
}

void	set_state(t_person *person, t_state state)
{
	pthread_mutex_lock(&person->state.mutex);
	person->state.value = state;
	pthread_mutex_unlock(&person->state.mutex);
}
