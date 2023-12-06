/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 22:06:38 by havyilma          #+#    #+#             */
/*   Updated: 2023/08/22 19:48:19 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_n(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (1);
	if (!str[1])
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	echo_pre_request(char *str)
{
	if (!str)
	{
		write(1, "\n", 1);
		return (0);
	}
	return (1);
}

char	*only_one(char	*tmp, int ctrl_n)
{
	char	*new;

	if (ctrl_n == 1)
	{
		new = ft_strjoin(tmp, "\n");
		free(tmp);
		return (new);
	}
	return (tmp);
}

char	*current_str(char **str, int index, char ctrl_n)
{
	char	*tmp;
	char	*new;

	new = NULL;
	tmp = ft_strdup(str[index++]);
	while (str[index] != NULL)
	{
		if (new)
			free(new);
		new = ft_strjoin_vol2(tmp, str[index]);
		if (tmp)
			free(tmp);
		tmp = ft_strdup(new);
		index++;
	}
	if (new == NULL)
		return (only_one(tmp, ctrl_n));
	if (ctrl_n == 1)
		new = ft_strjoin(tmp, "\n");
	free (tmp);
	return (new);
}

void	ft_echo(t_executable *exec, int i)
{
	char	ctrl_n;
	char	*tab;

	ctrl_n = 1;
	if (!(exec->str[1]) || exec->str[1] == NULL)
	{
		write(1, "\n", 1);
		return ;
	}
	while (exec->str[i])
	{
		ctrl_n = check_n(exec->str[i]);
		if (ctrl_n == 1)
		{
			if (check_n(exec->str[i - 1]) == 0)
				ctrl_n = 0;
			break ;
		}
		i++;
	}
	tab = (current_str(exec->str, i, ctrl_n));
	printf("%s", tab);
	if (tab)
		free(tab);
}
