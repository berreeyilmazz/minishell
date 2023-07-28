/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_t_executable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:56:44 by mkoroglu          #+#    #+#             */
/*   Updated: 2023/07/27 00:15:07 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (pipe(fd) == -1) // hata döndürmesi
			return (-1);
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
	exec->str = malloc(sizeof(char *) * (size + 1));
	if (!exec->str)
		return (0);//bu returnu kullanmadım hiç hata durumu
	exec->str[size] = NULL;
	size = 0;

	while (tokens && tokens->type == COMMAND)
	{
		exec->str[size] = ft_strdup(tokens->content);
		tokens = tokens->next;
		size++;
	}
	return (tokens);
}

int	ft_add_str_executable(void)
{
	t_token			*tokens;
	t_executable	*exec;
	t_token			*iter;
	int				i;
	int				a;

	a = 0;
	exec = g_global.exec;
	tokens = g_global.tokens;
	while (a <= g_global.pipe_cnt)
	{
		i = 0;
		while (tokens && tokens->type != COMMAND)
			tokens = tokens->next;
		iter = tokens;
		while (iter && iter->type == COMMAND)
		{
			iter = iter->next;
			i++;
		}
		tokens = ft_exec_strdup(exec, tokens, i);
		exec = exec->next;
		a++;
	}
	return (1);
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

int	ft_setting_t_executable(void)
{
	if (!ft_open_struct_executable())
		return (0); //hata malloc
	if (!ft_add_str_executable())
		return (0); //hata malloc
	if (g_global.pipe_cnt > 0)
		ft_pipe_cont_executable();//hata alma ifle işlenmedi
	ft_filename_redirection_executable(); //bunun retrun hata eklemedik
	return (1);
}