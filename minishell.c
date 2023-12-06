/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:26:05 by havyilma          #+#    #+#             */
/*   Updated: 2023/08/25 13:58:28 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	signal_handler();
	get_env(envp);
	fill_env_exp();
	get_line();
	return (0);
}

void	get_env(char **envp)
{
	int	i;
	int	cnt;

	cnt = 0;
	i = 0;
	while (envp[cnt])
		cnt++;
	g_global.envp = malloc(sizeof(char *) * (cnt + 1));
	while (i < cnt)
	{
		g_global.envp[i] = ft_strdup(envp[i]);
		i++;
	}
	g_global.envp[i] = NULL;
}

void	ft_continue(t_token **token)
{
	t_token	*tmp;

	while ((*token))
	{
		tmp = (*token)->next;
		free((*token)->content);
		free(*token);
		(*token) = tmp;
	}
}

void	ft_check(void)
{
	t_token	*token;

	token = g_global.tokens;
	while (token)
	{
		if (token->next && (!token->next->content 
				|| token->next->content[0] == '#'))
		{
			if (token->next)
			{
				if (token->next->next)
					ft_continue(&(token->next->next));
				free (token->next);
			}
			if (token->next->content)
				free (token->next->content);
			token->next = NULL;
			return ;
		}
		token = token->next;
	}
}

void	get_line(void)
{
	while (1)
	{
		ft_init();
		g_global.input = readline("minishell-$ ");
		eof_control_main(g_global.input);
		if (g_global.input[0] != 0)
			add_history(g_global.input);
		if (g_global.signal_status == -1 || g_global.input[0] == 0
			|| ft_get_tokens(-1, 0) == -1)
		{
			ft_free();
			continue ;
		}
		ft_check();
		if (ft_get_type() == -1)
		{
			ft_free();
			continue ;
		}
		ft_setting_t_executable();
		if (g_global.signal_status != -1)
			ft_execute_starter();
		ft_free_global();
	}
}
