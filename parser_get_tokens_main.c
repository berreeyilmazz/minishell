/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_tokens_main.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:57:28 by havyilma          #+#    #+#             */
/*   Updated: 2023/07/26 00:59:51 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	while_for_spaces(int i)
{
	while (g_global.input[i] && g_global.input[i] == ' ')
		i++;
	return (i);
}

int	while_for_nonspaces(int i)
{
	while ((g_global.input[i] && red_pipe_or_quote(i) == 0))
		i++;
	return (i);
}

int	ft_get_tokens(int i, int start)
{
	t_token	*token;

	token = g_global.tokens;
	while (g_global.input[++i])
	{
		start = while_for_spaces(i);
		i = while_for_nonspaces(start);
		if (g_global.input[i] && red_pipe_or_quote(i) == 1)
			i = ft_get_tokens_plus(start, i, &token);
		else if (g_global.input[i] && (g_global.input[i] == 34
				|| g_global.input[i] == 39))
			i = ft_get_word_for_quote(start, i, &token);
		else if (g_global.input[i] == 32 && start != i)
			i = ft_get_word(start, i, &token);
		else if (!g_global.input[i])
		{
			ft_words(start, i, &token);
			token->next = NULL;
			break ;
		}
		if (i == -1)
			break ;
	}
	return (i);
}
