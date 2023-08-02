/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 22:06:38 by havyilma          #+#    #+#             */
/*   Updated: 2023/08/02 09:44:27 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_n(char *str)
{
	int i;

	i = 1;
	if (str[0] != '-')
		return (1);
	while ((str[i]))
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int echo_pre_request(char	*str)
{
	if (!str)
	{
		write(1, "\n", 1);
		return (0);
	}
	return (1);
}

char *current_str(char **str, int index, char ctrl_n)
{
	char	*tmp;
	char	*new;

	new = NULL;
	tmp = ft_strdup(str[index]);
	index++;
	while (str[index])
	{
		new = ft_strjoin_vol2(tmp, str[index]);
		free(tmp);
		tmp = new;;
		free(new);
		index++;
	}
	if(!new)
	{	
		if (check_n(g_global.exec->str[1]) == 1)
			tmp[ft_strlen(tmp)] = '\n';
		return(tmp);
	}
	if (ctrl_n == 1)
		new = ft_strjoin(new, "\n");
	new = ft_strjoin(new, "\0");
	if(tmp)
		free(tmp);
	return (new);
}

void ft_echo(t_executable *exec)
{
	char ctrl_n;
	char *tab;
	int	i;
	
	i = 1;
	if (echo_pre_request(exec->str[1]) == 0)
		return;
	while(exec->str[i])
	{
		ctrl_n = check_n(exec->str[i]);
		if(ctrl_n == 1)
			break;
		i++;
	}
	tab = (current_str(exec->str, i, ctrl_n));
	printf("%s", tab);
	if(tab)
		free(tab);
}
