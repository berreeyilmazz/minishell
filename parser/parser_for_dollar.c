/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_for_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 01:43:36 by havyilma          #+#    #+#             */
/*   Updated: 2023/08/25 01:23:14 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_alpha(int index)
{
	if ((g_global.input[index] >= 65 && g_global.input[index] <= 90) 
		|| (g_global.input[index] >= 97 && g_global.input[index] <= 122))
	{
		index++;
		while ((g_global.input[index] >= 65 && g_global.input[index] <= 90) 
			|| (g_global.input[index] >= 97 && g_global.input[index] <= 122) 
			|| (g_global.input[index] >= 48 && g_global.input[index] <= 57))
		{
			index++;
			if (g_global.input[index] == '.' || g_global.input[index] == '=' 
				|| g_global.input[index] == '$')
				break ;
		}
	}
	else if (g_global.input[index] == '?')
		index++;
	return (index);
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
	index = skip_alpha(index);
	*start_dollar = index - 1;
	if (index == start)
		return (NULL);
	new = malloc(sizeof(char) * (index - start + 1));
	i = 0;
	while (start < index)
		new[i++] = g_global.input[start++];
	new[i] = '\0';
	return (new);
}

void	handler_one(t_token **token, int *j, int *ij, int p)
{
	int		k;
	char	*exit;
	int		i;

	i = *ij;
	k = *j;
	if (g_global.input[i] == '$' && (g_global.input[i + 1] == '?' 
			|| g_global.input[i + 1] == '#'))
	{
		p = 0;
		exit = ft_itoa(g_global.exit_status);
		while (exit[p])
			(*token)->content[k++] = exit[p++];
		free(exit);
		i += 1;
	}
	else if (g_global.input[i] == '$' && g_global.input[i + 1] == '$')
		i += 1;
	else if ((g_global.input[i] != '$' || (g_global.input[i] == '$' 
				&& (!ft_isalnum(g_global.input[i + 1]) 
					|| g_global.input[i + 1] == 32 || !g_global.input[i + 1]))))
		(*token)->content[k++] = g_global.input[i];
	*j = k;
	*ij = i;
}

int	handler_two(t_token **token, int *j, int *ij, int m)
{
	char	*word;
	char	*wanted;

	if (g_global.input[*ij] == '$')
	{
		word = is_it_alnum(ij);
		if (!word)
		{
			*ij += 1;
			return (1);
		}
		wanted = get_from_env(word);
		if (!wanted)
		{
			free (word);
			return (1);
		}
		while (wanted[m])
			(*token)->content[(*j)++] = wanted[m++];
		free (wanted);
		free (word);
	}
	return (0);
}

int	if_dollar_handler(t_token **token, int i, int end, int k)
{
	int	keep_i;
	int	keep_k;

	while (g_global.input[i] && i < end)
	{
		keep_i = i;
		keep_k = k;
		handler_one(token, &k, &i, 0);
		if (keep_i == i && keep_k == k)
			handler_two(token, &k, &i, 0);
		i++;
	}
	(*token)->content[k] = '\0';
	return (i);
}
