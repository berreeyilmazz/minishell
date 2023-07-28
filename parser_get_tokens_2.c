/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_tokens_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 06:11:26 by havyilma          #+#    #+#             */
/*   Updated: 2023/07/27 00:46:37 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_words(int i, int j, t_token **token)
{
	int	k;

	k = 0;
	if (i == j)
		return ;
	(*token)->content = malloc(sizeof(char) * (j - i + 1));
	while (i < j && g_global.input[i])
	{
		(*token)->content[k] = g_global.input[i];
		i++;
		k++;
	}
	(*token)->content[k] = '\0';
}

int	ft_get_word(int start, int end, t_token **token)
{
	ft_words(start, end, token);
	if (ft_check_if_next(end, token))
		ft_get_next(token);
	return (end);
}

int	ft_get_pipe_red(t_token **token, int i)
{
	if (g_global.input[i] == '|')
	{
		(*token)->content = ft_strdup("|");
		g_global.pipe_cnt++;
	}
	else if (g_global.input[i] == '>' && g_global.input[i + 1] == '>')
	{
		(*token)->content = ft_strdup(">>");
		i += 1;
	}
	else if (g_global.input[i] == '<' && g_global.input[i + 1] == '<')
	{
		(*token)->content = ft_strdup("<<");
		i += 1;
	}
	else if (g_global.input[i] == '>')
		(*token)->content = ft_strdup(">");
	else if (g_global.input[i] == '<')
		(*token)->content = ft_strdup("<");
	if (ft_check_if_next(i, token))
		ft_get_next(token);
	return (i);
}

int	ft_get_tokens_plus(int start, int i, t_token **token)
{
	if (start != i)
		i = ft_get_word(start, i, token);
	i = ft_get_pipe_red(token, i);
	return (i);
}
