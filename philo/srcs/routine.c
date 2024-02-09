/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycostode <ycostode@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 22:25:08 by ycostode          #+#    #+#             */
/*   Updated: 2024/02/08 16:52:40 by ycostode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	daily_eat(t_person *person)
{
	if (compare_current_time(person->last_meal)
		>= person->program->info.eat_time)
	{
		pthread_mutex_lock(&person->spare_fork->mutex);
		person->spare_fork->value = true;
		pthread_mutex_unlock(&person->spare_fork->mutex);
		person->spare_fork = NULL;
		pthread_mutex_lock(&person->fork.mutex);
		person->fork.value = true;
		pthread_mutex_unlock(&person->fork.mutex);
		person->meals++;
		set_state(person, HAS_EATEN);
		if (enough_meal(*person))
			return ;
		printf("\033[1;37m%llu \033[1;36m%d is sleeping\n\033[0m",
			current_time(*person->program), person->id + 1);
	}
}

void	daily_sleep(t_person *person)
{
	if (compare_current_time(person->last_meal)
		>= person->program->info.sleep_time)
		set_state(person, HAS_SLEPT);
}

bool	is_dead(t_program program)
{
	int	i;

	i = 0;
	while (i < program.number)
	{
		if (check_state(program.persons[i], DEAD))
			return (true);
		++i;
	}
	return (false);
}

bool	enough_meal(t_person person)
{
	if (person.program->info.meals == -1)
		return (false);
	return (person.meals >= person.program->info.meals);
}

void	die(t_person *person)
{
	if (check_state(*person, DEAD))
		return ;
	if (compare_current_time(person->last_meal)
		>= person->program->info.die_time)
	{
		printf("\033[1;37m%llu \033[1;31m%d died\n\033[0m",
			current_time(*person->program), person->id + 1);
		set_state(person, DEAD);
	}
}
