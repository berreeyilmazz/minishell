/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_for_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 06:19:57 by havyilma          #+#    #+#             */
/*   Updated: 2023/07/30 04:53:51 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
int	for_quotes(int start, int i, t_token **token)
{
	int	keep_start;
	int	keep_i;
	char	*tmp;

	keep_start = start;
	keep_i = i;
	while (start < i && g_global.input[start])
	{
		if (g_global.input[start] == '$')
		{
			free((*token)->content);
			if_dollar(token, keep_start, start, i);
			break;
		}
		start++;
	}
	ft_get_word_for_quote()
}
*/
int	ft_len(int start, int i, char quote, int cnt)
{
	while (g_global.input[start])
	{
		if (g_global.input[start] && g_global.input[start] != 34 && g_global.input[start] != 39 && g_global.input[start] != 32 && start < i)
			cnt++;
		else if (g_global.input[start] && (g_global.input[start] == 34 || g_global.input[start] == 39) && start < i)
		{
			if (quote == '\0')
				quote = g_global.input[start];
			else
			{
				if (g_global.input[start] == quote)
					quote = '\0';
				else
					cnt++;
			}
		}
		else if (g_global.input[start] && g_global.input[start] == 32)
		{
			if(quote == '\0')
			{
				quote = 32;
				break;
			}
			else
				cnt++;
		}
		start++;
	}
	if (quote != '\0')
		return (ft_print_cnf());
	return (cnt);
}

int ft_i(int start)
{
	char	quote;
	quote = '\0';
	
	int	i = start;
	while (g_global.input[start])
	{
		if (g_global.input[start] && g_global.input[start] != 34 && g_global.input[start] != 39 && g_global.input[start] != 32)
			i++;
		else if (g_global.input[start] && (g_global.input[start] == 34 || g_global.input[start] == 39))
		{
			if (quote == '\0')
				quote = g_global.input[start];
			else if (quote != '\0')
			{
				if (g_global.input[start] == quote)
				{
					quote = '\0';
					i++;
				}
				else
					i++;
			}
		}
		else if (g_global.input[start] && g_global.input[start] == 32)
		{
			if(quote == '\0')
			{
				i++;
				break;
			}
			else
				i++;
		}
		start++;
	}
	return (i + 1);
}

int ft_get_while(int start, int i, t_token **token, char quote)
{
	int j;

	j = 0;
	while (g_global.input[start])
	{
		if (g_global.input[start] && g_global.input[start] != 34 
		&& g_global.input[start] != 39 && start < i)
			(*token)->content[j++] = g_global.input[start];
		else if (g_global.input[start] && (g_global.input[start] == 34 || g_global.input[start] == 39) && start < i)
		{
			if (quote == '\0')
				quote = g_global.input[start];
			else
			{
				if (g_global.input[start] == quote)
					quote = '\0';
				else
					(*token)->content[j++] = g_global.input[start];
			}
		}
		start++;
	}
	(*token)->content[j] = '\0';
	return (1);
}

int ft_get_word_for_quote(int start, int i, t_token **token)
{
	int j;
	int len;

	j = 0;
	i = ft_i(i);
	len = ft_len(start, i, '\0', 0);
	if (len == -1)
		return (-1);
	(*token)->content = malloc(sizeof(char) * len + 1);
	ft_get_while(start, i, token, '\0');
	if ((*token)->content[0] && ft_strlen((*token)->content) == 1)
		(*token)->type = FILENAME;
	if (ft_check_if_next(i, token))
		ft_get_next(token);
	return (i);
}
