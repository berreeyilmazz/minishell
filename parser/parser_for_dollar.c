/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_for_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 01:43:36 by havyilma          #+#    #+#             */
/*   Updated: 2023/08/04 12:56:01 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_from_env(char *word)
{
	int	i;
	char	*rtrn;
	t_env	*env;

	env = g_global.env;
	i = 0;
	while(env)
	{
		if(ft_strcmp(env->line, word) == '=')
		{
			rtrn = ft_substr(env->line, ft_strlen(word) + 1, ft_strlen(env->line));
			return (rtrn);
		}
		env = env->next;
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


int	if_dollar_handler(t_token **token, int i, int end, int k)
{
	char	*word;
	char	*wanted;
	int		j;
	
	wanted = 0;
	while(g_global.input[i] && i != end)
	{
		if(g_global.input[i] != '$' && i != end)
			(*token)->content[k++] = g_global.input[i];
		if(g_global.input[i] == '$' && i != end)
		{
			j = 0;
			word = is_it_alnum(&i);
			wanted = get_from_env(word);
			if(!wanted)
				return (1);
			while(wanted[j])
				(*token)->content[k++] = wanted[j++];
			i--;
		}
		i++;
	}
	(*token)->content[k] = '\0';
	free(word);
	free(wanted);
	return(0);	
}

int	if_dollar_counter(int i, int end, int len)
{
	char	*word;
	char	*wanted;

	wanted = 0;
	while(g_global.input[i] && i != end)
	{
		if(g_global.input[i] != '$' && i != end)
			len++;
		if(g_global.input[i] == '$' && i != end)
		{
			word = is_it_alnum(&i);
			wanted = get_from_env(word);
			if(!wanted)
				return (-1);
	        free(word);
			len += ft_strlen(wanted);
			i--;
		}
		i++;
	}
	free(wanted);
	return (len);
}

int turning_into_env(int   *m, t_token **token, int *index)
{
    char    *word;
    char    *wanted;
    int     k;
    int     in;
    int     i;

    i = *m;
    in = *index;
    k = 0;
    word = is_it_alnum(&i);
    wanted = get_from_env(word);
    free(word);
    if(!wanted)
        return (-1);
    while(wanted[k])
        (*token)->content[in++] = wanted[k++];
	(*token)->content[in] = '\0';
    free(wanted);
    *index = in;
    *m = i;
    return (1);
}