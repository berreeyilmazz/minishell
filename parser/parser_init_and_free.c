/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init_and_free.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 06:11:33 by havyilma          #+#    #+#             */
/*   Updated: 2023/08/03 01:29:37 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (token->content)
			free(token->content);
		free(token);
		token = tmp;
	}
	g_global.tokens = 0;
	free(g_global.input);
}

void	ft_free_global(void)
{
	t_executable	*exec;
	t_executable	*tmp;

	exec = g_global.exec;
	while (exec)
	{
		tmp = exec->next;
		ft_free_double_pointer(exec->str);
		free(exec);
		exec = tmp;
	}
	if (g_global.exit_status)
		free(g_global.exit_status);
	g_global.exec = 0;
	ft_free();
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
