/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar_and_quote.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 19:54:05 by havyilma          #+#    #+#             */
/*   Updated: 2023/08/25 04:11:02 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dollar_handler_plus(int i, int *j, t_token **token, int p)
{
	char	*word;
	char	*wanted;
	int		k;

	k = *j;
	word = is_it_alnum(&i);
	if (!word)
	{
		i += ft_strlen(word);
		return (i);
	}
	wanted = get_from_env(word);
	if (word)
		free(word);
	if (!wanted)
		return (i);
	while (wanted[p])
		(*token)->content[k++] = wanted[p++];
	if (wanted)
		free(wanted);
	*j = k;
	return (i);
}

int	dollar_handler_for_quote(t_token **token, int i, int end, int *j)
{
	char	*wanted;
	int		p;
	int		k;

	k = *j;
	wanted = 0;
	if (g_global.input[i] == '$' && (g_global.input[i + 1] == '?' 
			|| g_global.input[i + 1] == '#'))
	{
		p = 0;
		wanted = ft_itoa(g_global.exit_status);
		while (wanted && wanted[p])
			(*token)->content[k++] = wanted[p++];
		free(wanted);
		i++;
	}
	else if (g_global.input[i] == '$' && g_global.input[i + 1] == '$')
		i += 0;
	else if (g_global.input[i] == '$' && i < end)
		i = dollar_handler_plus(i, &k, token, 0);
	*j = k;
	return (i);
}

int	dollar_plus(int *ij, int len)
{
	int		i;
	char	*word;
	char	*wanted;

	i = *ij;
	word = is_it_alnum(&i);
	if (!word)
	{
		i++;
		*ij = i;
		return (len);
	}
	wanted = get_from_env(word);
	free (word);
	if (!wanted)
	{
		*ij = i;
		return (len);
	}
	len += ft_strlen(wanted);
	free(wanted);
	i--;
	*ij = i;
	return (len);
}

int	dollar_counter_for_quote(int *ij, int end, int len)
{
	char	*wanted;
	int		i;

	i = *ij;
	wanted = 0;
	if (g_global.input[i] == '$' && (g_global.input[i + 1] == '?'
			|| g_global.input[i + 1] == '#'))
	{
		wanted = ft_itoa(g_global.exit_status);
		len += ft_strlen(wanted);
		free(wanted);
		i += 1;
	}
	else if (g_global.input[i] == '$' && g_global.input[i + 1] == '$')
		i += 1;
	else if (g_global.input[i] == '$' && !ft_isalnum(g_global.input[i + 1]))
	{
		len += 1;
		i += 1;
	}
	else if (g_global.input[i] == '$' && i != end)
		len = dollar_plus(&i, len);
	*ij = i;
	return (len);
}

int	ft_get_word_for_quote(int start, int i, t_token **token)
{
	int	len;
	int	c;

	i = ft_i(i);
	len = ft_len(start, i, '\0', 0);
	if (len <= 0)
	{
		(*token)->content = NULL;
		(*token)->next = NULL;
		return (i);
	}
	(*token)->content = malloc(sizeof(char) * (len + 1));
	ft_get_while(start, i, token, '\0');
	ft_check_content(token, (*token)->content);
	c = ft_check_if_next(i + 1, token);
	if (c == 1)
		ft_get_next(token);
	else if (c == 0)
		return (i);
	return (i);
}
