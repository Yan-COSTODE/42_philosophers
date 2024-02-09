/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycostode <ycostode@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 22:24:09 by ycostode          #+#    #+#             */
/*   Updated: 2024/01/31 12:26:36 by ycostode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		++i;
	return (i);
}

bool	atot_convert(const char *s, t_time *n)
{
	int		i;
	long	tmp;

	i = 0;
	*n = 0;
	tmp = 0;
	if (s[i] == '-')
		return (false);
	if (s[i] == '+')
		++i;
	while (s[i] == '0')
		++i;
	if (ft_strlen(&s[i]) > 10 || (ft_strlen(&s[i]) == 0 && s[i - 1] != '0'))
		return (false);
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (false);
		tmp = tmp * 10 + (s[i] - '0');
		++i;
	}
	if (tmp > INT_MAX)
		return (false);
	*n = tmp;
	return (true);
}

bool	atoi_convert(const char *s, int *n)
{
	int		i;
	long	tmp;

	i = 0;
	*n = 0;
	tmp = 0;
	if (s[i] == '-')
		return (false);
	if (s[i] == '+')
		++i;
	while (s[i] == '0')
		++i;
	if (ft_strlen(&s[i]) > 10 || (ft_strlen(&s[i]) == 0 && s[i - 1] != '0'))
		return (false);
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (false);
		tmp = tmp * 10 + (s[i] - '0');
		++i;
	}
	if (tmp > INT_MAX)
		return (false);
	*n = tmp;
	return (true);
}

t_time	compare_current_time(struct timeval time)
{
	struct timeval	other_time;
	long long		result_sec;
	long long		result_usec;

	gettimeofday(&other_time, NULL);
	result_sec = other_time.tv_sec - time.tv_sec;
	result_usec = other_time.tv_usec - time.tv_usec;
	return ((result_sec * 1000000) + result_usec);
}

t_time	current_time(t_program program)
{
	struct timeval	time;
	long long		result_sec;
	long long		result_usec;

	gettimeofday(&time, NULL);
	result_sec = time.tv_sec - program.time.tv_sec;
	result_usec = time.tv_usec - program.time.tv_usec;
	return ((result_sec * 1000) + (result_usec / 1000));
}
