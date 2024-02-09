/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycostode <ycostode@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:15:49 by ycostode          #+#    #+#             */
/*   Updated: 2024/02/08 16:40:07 by ycostode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*daily_routine(void *param)
{
	t_person	*person;

	person = (t_person *)param;
	while (!is_dead(*person->program) && !enough_meal(*person))
	{
		if (check_state(*person, THINKING))
			take_fork(person);
		if (check_state(*person, HAS_FORK))
			daily_eat(person);
		if (check_state(*person, HAS_EATEN))
			daily_sleep(person);
		if (check_state(*person, HAS_SLEPT))
		{
			printf("\033[1;37m%llu \033[1;35m%d is thinking\n\033[0m",
				current_time(*person->program), person->id + 1);
			set_state(person, THINKING);
		}
		die(person);
		usleep(8);
	}
	return (NULL);
}

t_person	init_person(t_program *program, int id)
{
	t_person	person;

	person.id = id;
	person.program = program;
	person.spare_fork = NULL;
	pthread_mutex_init(&person.fork.mutex, NULL);
	pthread_mutex_init(&person.state.mutex, NULL);
	person.fork.value = true;
	person.meals = 0;
	person.state.value = THINKING;
	printf("\033[1;37m%llu \033[1;35m%d is thinking\n\033[0m",
		current_time(*program), id + 1);
	gettimeofday(&person.last_meal, NULL);
	return (person);
}

void	start_thread(t_program *program)
{
	int	i;
	int	j;
	int	implement;

	if (program->number % 2 == 0)
		implement = 2;
	else
		implement = 3;
	j = 0;
	while (j < implement)
	{
		i = j;
		while (i < program->number)
		{
			pthread_create(&program->persons[i].thread, NULL, daily_routine,
				&program->persons[i]);
			i += implement;
		}
		j++;
		usleep(1000);
	}
}

void	start(t_program *program)
{
	int	i;

	program->info.die_time *= 1000;
	program->info.eat_time *= 1000;
	program->info.sleep_time *= 1000;
	program->info.sleep_time += program->info.eat_time;
	program->persons = (t_person *)malloc(program->number * sizeof(t_person));
	if (!program->persons)
		return ;
	i = -1;
	while (++i < program->number)
		program->persons[i] = init_person(program, i);
	start_thread(program);
	i = -1;
	while (++i < program->number)
		pthread_join(program->persons[i].thread, NULL);
	i = -1;
	while (++i < program->number)
	{
		pthread_mutex_destroy(&program->persons[i].fork.mutex);
		pthread_mutex_destroy(&program->persons[i].state.mutex);
	}
	free(program->persons);
}

int	main(int argc, char **argv)
{
	t_program	program;

	if (argc < 5 || argc > 6)
		return (EXIT_FAILURE);
	if (gettimeofday(&program.time, NULL) != 0)
		return (EXIT_FAILURE);
	if (!atoi_convert(argv[1], &program.number) && program.number > 124124)
		return (EXIT_FAILURE);
	if (!atot_convert(argv[2], &program.info.die_time))
		return (EXIT_FAILURE);
	if (!atot_convert(argv[3], &program.info.eat_time))
		return (EXIT_FAILURE);
	if (!atot_convert(argv[4], &program.info.sleep_time))
		return (EXIT_FAILURE);
	if (argc == 5)
		program.info.meals = -1;
	else if (!atoi_convert(argv[5], &program.info.meals))
		return (EXIT_FAILURE);
	start(&program);
	return (EXIT_SUCCESS);
}
