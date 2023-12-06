/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_not_clear_but_okey.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:31:13 by havyilma          #+#    #+#             */
/*   Updated: 2023/08/25 04:10:26 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_dollar_plus(int *i, int *len)
{
	char	*word;
	char	*wanted;

	word = is_it_alnum(i);
	if (!word)
	{
		*i += 1;
		return (1);
	}
	wanted = get_from_env(word);
	if (word)
		free(word);
	if (!wanted)
	{
		*i += 1;
		return (1);
	}
	*len += ft_strlen(wanted);
	if (wanted)
		free(wanted);
	*i -= 1;
	return (0);
}

int	just_dollar(int *i, int *len)
{
	if (g_global.input[*i] != '$')
	{
		*len += 1;
		return (0); 
	}
	if (g_global.input[*i] == '$' && g_global.input[(*i) + 1] == '$')
		*i += 1;
	else if (g_global.input[*i] == '$' && (!ft_isalnum(g_global.input[(*i) + 1])
			|| g_global.input[(*i) + 1] == 32 || !g_global.input[(*i) + 1]))
	{
		*len += 1;
		*i += 1;
		return (1);
	}
	return (0);
}

int	if_dollar_counter(int i, int end, int len)
{
	char	*wanted;

	wanted = 0;
	while (g_global.input[i] && i < end)
	{
		if (g_global.input[i] == '$' 
			&& (g_global.input[i + 1] == '?' || g_global.input[i + 1] == '#'))
		{
			wanted = ft_itoa(g_global.exit_status);
			len += ft_strlen(wanted);
			if (wanted)
				free(wanted);
		}
		if (just_dollar(&i, &len))
			i++;
		if (g_global.input[i] == '$' && i != end)
			if (if_dollar_plus(&i, &len) == 1)
				continue ;
		i++;
	}
	return (len);
}
