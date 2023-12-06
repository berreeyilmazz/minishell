/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 06:11:11 by havyilma          #+#    #+#             */
/*   Updated: 2023/08/25 02:48:59 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_print_cnf(void)
{
	printf("minishell: command not found\n");
	g_global.exit_status = 127;
	return (-1);
}

int	unexpected_token(void)
{
	printf("minishell: unexpected token\n");
	return (-1);
}

int	ft_syntax_error(void)
{
	printf("minishell: syntax error near unexpected token ''\n");
	g_global.exit_status = 258;
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
	else if (g_global.input[i] == ' ' || g_global.input[i] == 13)
		return (32);
	return (0);
}

void	ft_get_next(t_token **tmp)
{
	(*tmp)->next = malloc(sizeof(t_token));
	(*tmp) = (*tmp)->next;
	(*tmp)->content = NULL;
	(*tmp)->type = 0;
}
