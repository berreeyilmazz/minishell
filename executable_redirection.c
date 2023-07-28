/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filename_redirection_executable.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 17:59:08 by mkoroglu          #+#    #+#             */
/*   Updated: 2023/07/27 00:57:07 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//yaoılmadı heredoc
//
int	ft_db_i(t_executable *exec, t_token *tokens)
{
	int	fd;

	tokens = tokens->next;
	if (tokens->type == FILENAME)
	{
		fd = open(tokens->content, O_CREAT | O_RDWR, 0777);
		if (fd == -1)
			return (0); ///hata mesajı!!!!????
		if (exec->fd_output > 2)
			close(exec->fd_output);
		exec->fd_output = fd;
	}
	return (1);
}

int	ft_db_o(t_executable *exec, t_token *tokens)
{
	int	fd;

	tokens = tokens->next;
	if (tokens->type == FILENAME)
	{
		fd = open(tokens->content, O_CREAT | O_RDWR | O_APPEND , 0777);
		if (fd == -1)
			return (0); ///hata mesajı!!!!????
		if (exec->fd_output > 2)
			close(exec->fd_output);
		exec->fd_output = fd;
	}
	return (1);
}

int	ft_red_i(t_executable *exec, t_token *tokens)
{
	int	fd;

	tokens = tokens->next;
	if (tokens->type == FILENAME)
	{
		fd = open(tokens->content, O_CREAT | O_RDONLY, 0777);
		if (fd == -1)
			return (0);
		//hata mesajı!!!!????
		if (exec->fd_input > 2)
			close(exec->fd_input);
		
		exec->fd_input = fd;
	}
	return (1);
}

int	ft_red_o(t_executable *exec, t_token *tokens)
{
	int	fd;

	tokens = tokens->next;
	if (tokens->type == FILENAME)
	{
		fd = open(tokens->content, O_CREAT | O_RDWR | O_TRUNC, 0777);
		if (fd == -1)
			return (0); ///hata mesajı!!!!????
		if (exec->fd_output > 2)
			close(exec->fd_output);
		exec->fd_output = fd;
	}
	return (1);
}

int	ft_filename_redirection_executable(void)
{
	t_executable	*exec;
	t_token			*tokens;

	exec = g_global.exec;
	tokens = g_global.tokens;
	while (tokens)
	{
		if (tokens->type == PIPE)
			exec = exec->next;
		else if (tokens->type == RED_I)
			ft_red_i(exec, tokens);
		else if (tokens->type == RED_O)
			ft_red_o(exec, tokens);
		else if (tokens->type == DB_I)
			ft_db_i(exec, tokens);
		else if (tokens->type == DB_O)
			ft_db_o(exec, tokens);
		tokens = tokens->next;
	}
	return (1);
}
