/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_tokens_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 06:11:26 by havyilma          #+#    #+#             */
/*   Updated: 2023/07/30 05:08:15 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_from_env(char *word)
{
	int	i;
	char	*rtrn;

	i = 0;
	while(g_global.env[i])
	{
		if(ft_strcmp(g_global.env[i], word))
		{
			rtrn = ft_substr(g_global.env[i], ft_strlen(word) + 1, ft_strlen(g_global.env[i]));
			return (rtrn);
		}
		i++;
	}
	return (NULL);
}

char	*is_it_alnum(int *start_dollar)
{
	int		start;
	char	*new;
	int		i;
	int		index;
	
	index = *start_dollar;
	index++;
	start = index;
	i = 0;
	while(g_global.input[index])
	{
		if(!((g_global.input[index] >= 65 && g_global.input[index] <= 90) 
		|| (g_global.input[index] >= 97 && g_global.input[index] <= 122) 
		|| (g_global.input[index] >= 48 && g_global.input[index] <= 57)) || g_global.input[index] == '.')
			break;
		index++;
	}
	new = malloc(sizeof(char)* (index - start + 1));
	while(start < index)
		new[i++] = g_global.input[start++];
	*start_dollar = index;
	new[i] = '\0';
	return (new);
}

char	*ft_before(int *befor, int *start_dolla)
{
	int		i;
	int		before;
	int		start_dollar;
	char	*first;
	
	i = 0;
	before = *befor;
	start_dollar = *start_dolla;
	first = NULL;
	while(before < start_dollar)
	{
		if(i == 0)
			first = malloc(sizeof(start_dollar - before + 1));
		first[i] = g_global.input[before];
		before++;
		i++;
	}
	if(!first)
		return(NULL);
	*befor = before;
	*start_dolla = start_dollar;
	first[i] = '\0';
	return (first);
}
int	if_dollar(t_token **token, int before, int start_dollar, int end)
{
	int		i;
	char	*dollr;
	char	*first;
	char	*last;
	char	*word;

	i = 0;
	first = ft_before(&before, &start_dollar);
	word = is_it_alnum(&start_dollar);
	dollr = get_from_env(word);
	free(word);
	if(!dollr)
		(*token)->content = ft_strdup(first);
	else if(!first)
		(*token)->content = ft_strdup(dollr);
	else
		(*token)->content = ft_strjoin(first, dollr);
	free(first);
	free(dollr);
	if(start_dollar < end)
	{
		last =  ft_substr(g_global.input, start_dollar, end);
		first = ft_strjoin((*token)->content,last);
		free((*token)->content);
		free(last);
		(*token)->content = ft_strdup(first);
		free(first);
	}
	return (1);
}


void	ft_words(int i, int j, t_token **token)
{
	int	k;
	int	keep_i;
	
	k = 0;
	keep_i = i;
	if (i == j)
		return ;
	(*token)->content = malloc(sizeof(char) * (j - i + 1));
	while (i < j && g_global.input[i])
	{
		if (g_global.input[i] == '$')
		{
			free((*token)->content);
			if_dollar(token, keep_i, i, j);
			return;
		}
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
