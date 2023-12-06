/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:56:44 by mkoroglu          #+#    #+#             */
/*   Updated: 2023/08/24 18:08:06 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pipe_cont_executable(void)
{
	t_executable	*exec;
	int				i;
	int				*fd;

	exec = g_global.exec;
	i = 0;
	while (i < g_global.pipe_cnt)
	{
		fd = 0;
		fd = malloc(sizeof(int) * 2);
		if (fd == NULL)
			return (0);
		if (pipe(fd) == -1)
			return (0);
		exec->fd_output = fd[1];
		exec->next->fd_input = fd[0];
		exec = exec->next;
		if (fd != NULL)
			free (fd);
		i++;
	}
	return (1);
}

t_token	*ft_exec_strdup(t_executable *exec, t_token *tokens, int size)
{
	int	i;

	i = 0;
	exec->str = malloc(sizeof(char *) * (size + 1));
	if (!exec->str)
		return (0);
	exec->str[size] = NULL;
	while (tokens)
	{
		if (tokens->type == PIPE)
			return (tokens->next);
		if (i < size && tokens->type == COMMAND)
		{
			exec->str[i] = ft_strdup(tokens->content);
			i++;
		}
		tokens = tokens->next;
	}
	return (tokens);
}

void	ft_add_str_executable(void)
{
	t_executable	*exec;
	t_token			*tokens;
	t_token			*iter;
	int				size;
	int				a;

	a = 0;
	exec = g_global.exec;
	tokens = g_global.tokens;
	while (a <= g_global.pipe_cnt)
	{
		size = 0;
		iter = tokens;
		while (iter && iter->type != PIPE)
		{
			if (iter->type == COMMAND)
				size++;
			iter = iter->next;
		}
		tokens = ft_exec_strdup(exec, tokens, size);
		exec = exec->next;
		a++;
	}
}

int	ft_open_struct_executable(void)
{
	t_executable	*exec;
	t_executable	*tmp;
	int				i;

	i = 0;
	exec = malloc(sizeof(t_executable));
	if (exec == NULL)
		return (0);
	ft_zero_struct_executable(exec);
	g_global.exec = exec;
	tmp = exec;
	while (i < g_global.pipe_cnt)
	{
		tmp->next = malloc(sizeof(t_executable));
		if (tmp->next == NULL)
			return (0);
		tmp = tmp->next;
		ft_zero_struct_executable(tmp);
		i++;
	}
	return (1);
}

void	ft_setting_t_executable(void)
{
	ft_open_struct_executable();
	ft_add_str_executable();
	if (g_global.pipe_cnt > 0)
		ft_pipe_cont_executable();
	ft_filename_redirection_executable();
}
