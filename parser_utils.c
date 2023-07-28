/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 06:11:11 by havyilma          #+#    #+#             */
/*   Updated: 2023/07/27 00:08:51 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_cnf(void)
{
	printf("unexpected token\n");
	return (-1);
}

int	ft_syntax_error(void)
{
	printf("syntax error near unexpected token `newline'\n");
	return (-1);
}

int	red_pipe_or_quote(int i)
{
	if (g_global.input[i] == '|' || g_global.input[i] == '>'
		|| g_global.input[i] == '<')
		return (1);
	else if (g_global.input[i] == 34)
		return (34);
	else if (g_global.input[i] == 39)
		return (39);
	else if (g_global.input[i] == ' ')
		return (32);
	return (0);
}

int	ft_check_if_next(int i, t_token **token)
{
	while (g_global.input[i])
	{
		i++;
		if (g_global.input[i] && g_global.input[i] != 32)
			return (1);
	}
	(*token)->next = NULL;
	return (0);
}

void	ft_get_next(t_token **tmp)
{
	(*tmp)->next = malloc(sizeof(t_token));
	(*tmp) = (*tmp)->next;
}
