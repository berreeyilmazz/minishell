/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 01:23:46 by havyilma          #+#    #+#             */
/*   Updated: 2023/08/25 03:53:02 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_pre_request(char **str)
{
	int	i;

	i = 1;
	while ((str[i]))
		i++;
	return (i);
}

int	is_it_numeric(char *str, int one_or_more)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= 48 && str[i] <= 57) && str[i] != '-' && str[i] != '+')
		{
			printf("exit\nexit: %s: numeric argument required\n", str);
			g_global.exit_status = 255;
			exit (255);
		}
		i++;
	}
	if (one_or_more == 2)
	{
		g_global.exit_status = ft_atoi(str);
		printf("exit\n");
		exit (g_global.exit_status);
	}
	else if (one_or_more > 2)
	{
		g_global.exit_status = 1;
		printf("exit\nexit: too many arguments\n");
	}
	return (0);
}

int	ft_exit(t_executable *exec)
{
	int	argc;

	if (g_global.pipe_cnt > 0)
		return (0);
	argc = exit_pre_request(exec->str);
	if (argc == 1)
	{
		printf("exit\n");
		g_global.exit_status = 1;
		exit(1);
	}
	else if (argc >= 2)
		is_it_numeric(exec->str[1], argc);
	return (0);
}
