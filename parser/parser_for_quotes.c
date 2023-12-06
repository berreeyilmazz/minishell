/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_for_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 06:19:57 by havyilma          #+#    #+#             */
/*   Updated: 2023/08/25 03:41:54 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_len_plus(int *cnt, char *quote, int start)
{
	if (g_global.input[start] 
		&& (g_global.input[start] == 34 || g_global.input[start] == 39))
	{
		if (*quote == '\0')
			*quote = g_global.input[start];
		else
		{
			if (g_global.input[start] == *quote)
				*quote = '\0';
			else
				*cnt += 1;
		}
	}
	return (1);
}

int	ft_len(int start, int i, char quote, int cnt)
{
	while (g_global.input[start] && start <= i)
	{
		if (g_global.input[start] == '$' && quote != 39)
		{
			cnt += dollar_counter_for_quote(&start, i, 0);
			if (cnt < -1)
				cnt = 0;
		}
		else if (g_global.input[start] && g_global.input[start] != 34 
			&& g_global.input[start] != 39 && g_global.input[start] != 32)
			cnt++;
		ft_len_plus(&cnt, &quote, start);
		if (g_global.input[start] && g_global.input[start] == 32)
		{
			if (quote == '\0')
				break ;
			else
				cnt++;
		}
		start++;
	}
	if (quote != '\0' && !g_global.input[start + 1])
		return (unexpected_token());
	return (cnt);
}

int	ft_i(int start)
{
	char	quote;
	int		i;
	int		nevermind;

	nevermind = 0;
	i = start;
	quote = '\0';
	while (g_global.input[i])
	{
		i += ft_len_plus(&nevermind, &quote, i);
		if (quote == '\0' 
			&& (g_global.input[start] == 32 || red_pipe_or_quote(i) == 1))
			return (i);
		if (g_global.input[i] && g_global.input[i] == 32)
		{
			if (quote == '\0')
				break ;
			else
				i++;
		}
	}
	return (i);
}

void	ft_get_while_plus(t_token **token, int *start, int *j, char quote)
{
	int		keep_start;
	char	*word;

	if (g_global.input[*start] == '$' && quote != 39)
	{
		keep_start = *start;
		word = is_it_alnum(&keep_start);
		if (word)
			free (word);
		if (keep_start != *start)
			*start = dollar_handler_for_quote(token, *start, keep_start, j);
		else
			(*token)->content[(*j)++] = '$';
	}
	else if (g_global.input[*start] == '$')
		(*token)->content[(*j)++] = g_global.input[*start];
}

int	ft_get_while(int start, int i, t_token **token, char quote)
{
	int		j;

	j = 0;
	while (g_global.input[start] && start < i)
	{
		if (g_global.input[start] == '$')
			ft_get_while_plus(token, &start, &j, quote);
		else if (g_global.input[start] && is_it_quote(start) == 2)
			(*token)->content[j++] = g_global.input[start];
		else if (g_global.input[start] && is_it_quote(start) == 1)
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
