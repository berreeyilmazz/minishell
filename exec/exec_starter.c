/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_starter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 19:31:27 by mkoroglu          #+#    #+#             */
/*   Updated: 2023/08/25 13:55:42 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_close_fd(void)
{
	t_executable	*exec;

	exec = g_global.exec;
	while (exec)
	{
		if (exec->fd_input > 2)
			close (exec->fd_input);
		if (exec->fd_output > 2)
			close (exec->fd_output);
		exec = exec->next;
	}
}

int	ft_heredoc(char *str_endline, int fd_input)
{
	char	*input;

	signal(SIGUSR1, ft_sig_chield);
	ft_close_fd();
	while (1)
	{
		input = readline("> ");
		eof_control_heredoc(input);
		if (!ft_strncmp(str_endline, input, ft_strlen(input) + 1))
			break ;
		write(fd_input, input, ft_strlen(input));
		write(fd_input, "\n", 1);
		if (input)
			free(input);
	}
	if (input)
		free(input);
	close (fd_input);
	exit(1);
}

int	ft_execute_main(t_executable **exec)
{
	if (!(*exec)->str)
	{
		*exec = (*exec)->next;
		return (1);
	}
	if (!ft_strcmp("cd", (*exec)->str[0]))
		ft_cd(*exec);
	else if (!ft_strcmp("exit", (*exec)->str[0]))
		ft_exit(*exec);
	else if (!ft_strcmp("export", (*exec)->str[0]) && (*exec)->str[1])
		ft_export_plus(*exec);
	else if (!ft_strcmp("unset", (*exec)->str[0]))
		ft_unset(*exec);
	else
		return (0);
	*exec = (*exec)->next;
	return (1);
}

void	ft_execute_chield(t_executable *exec)
{
	dup2(exec->fd_input, 0);
	dup2(exec->fd_output, 1);
	ft_close_fd();
	if (!ft_strcmp("echo", exec->str[0]))
		ft_echo(exec, 1);
	else if (!ft_strcmp("pwd", exec->str[0]))
		ft_pwd();
	else if (!ft_strcmp("export", exec->str[0]) && !exec->str[1])
		ft_export();
	else if (!ft_strcmp("env", exec->str[0]))
		ft_env();
	else
		ft_execve(exec);
	exit(0);
}

int	ft_execute_starter(void)
{
	t_executable	*exec;

	exec = g_global.exec;
	while (exec)
	{
		if (ft_execute_main(&exec))
			continue ;
		exec->pid = fork();
		if (exec->pid == 0)
			ft_execute_chield(exec);
		if (exec->pid == -1)
			return (0);
		exec = exec->next;
	}
	ft_close_fd();
	ft_wait_pid();
	return (1);
}
