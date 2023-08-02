/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init_and_free.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 06:11:33 by havyilma          #+#    #+#             */
/*   Updated: 2023/08/02 10:14:28 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init(void)
{
	g_global.tokens = malloc(sizeof(t_token));
	g_global.pipe_cnt = 0;
	g_global.input = 0;
	g_global.tokens->next = 0;
	g_global.tokens->content = 0;
}

void	ft_free(void)
{
	t_token	*token;
	t_token	*tmp;

	token = g_global.tokens;
	while (token)
	{
		tmp = token->next;
		free(token->content);
		free(token);
		token = tmp;
	}
	free(g_global.input);
}

void	write_global(void)
{
	t_token	*tmp;

	tmp = g_global.tokens;
	while (tmp)
	{
		if (tmp->next == NULL)
		{
			printf("=> content[%s]    ------  [%d]\n", tmp->content, tmp->type);
			break ;
			return ;
		}
		else
		{
			printf("-> content[%s]   ++++++  type[%d] \n", tmp->content,
				tmp->type);
			tmp = tmp->next;
		}
	}
}
