/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init_and_free.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 06:11:33 by havyilma          #+#    #+#             */
/*   Updated: 2023/08/25 03:23:46 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init(void)
{
	g_global.tokens = malloc(sizeof(t_token));
	g_global.pipe_cnt = 0;
	g_global.input = 0;
	g_global.signal_status = 0;
	g_global.heredoc_pid = -1;
	g_global.stdout_control = dup(1);
	g_global.tokens->next = 0;
	g_global.tokens->content = 0;
	g_global.tokens->type = 0;
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
	if (g_global.input)
		free(g_global.input);
}

void	ft_free_global(void)
{
	t_executable	*exec;
	t_executable	*tmp;

	ft_close_fd();
	exec = g_global.exec;
	while (exec)
	{
		tmp = exec->next;
		ft_free_double_pointer(exec->str);
		free(exec);
		exec = tmp;
	}
	g_global.exec = 0;
	ft_free();
}

int	is_it_quote(int i)
{
	if (g_global.input[i] == 34 || g_global.input[i] == 39)
		return (1);
	else if (g_global.input[i] != 34 && g_global.input[i] != 39)
		return (2);
	return (0);
}

char	*get_from_env(char *word)
{
	int		i;
	char	*rtrn;
	t_env	*env;

	env = g_global.env;
	while (env)
	{
		i = 0;
		while (env->line[i] == word[i])
			i++;
		if (env->line[i] == '=' && !word[i])
		{
			rtrn = ft_substr(env->line, 
					ft_strlen(word) + 1, ft_strlen(env->line));
			return (rtrn);
		}
		env = env->next;
	}
	return (NULL);
}
