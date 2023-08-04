/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_starter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 19:31:27 by mkoroglu          #+#    #+#             */
/*   Updated: 2023/08/04 13:03:14 by havyilma         ###   ########.fr       */
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

	while (1)
	{
		input = readline("> ");
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
	ft_close_fd();
	exit(1);
}

int	ft_execute_main(t_executable *exec)
{
	//if (g_global.pipe_cnt > 0)
		//return (0); //Buna çalışan dosyada bakman lazım.
	if (!exec->str)
		return (1);
	if (!ft_strcmp(exec->str[0], "cd"))
		ft_cd(exec);
	else if (!ft_strcmp(exec->str[0], "exit"))
		ft_exit(exec);
	else if (!ft_strcmp(exec->str[0], "export") && exec->str[1])
		ft_export_plus(exec);     
//	else if (!ft_strcmp(exec->str[0], "unset"));
	else
		return (0);
	return (1);
}

//hatalardan ötürü retrn ihtiyacı duaybilir.
void	ft_execute_chield(t_executable *exec)
{   
	dup2(exec->fd_input, 0);
	dup2(exec->fd_output, 1);
	ft_close_fd();
	if (!ft_strcmp(exec->str[0], "echo"))
		ft_echo(exec);
	else if (!ft_strcmp(exec->str[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(exec->str[0], "export") && !exec->str[1])
		ft_export();
	else if (!ft_strcmp(exec->str[0], "env"))
		ft_env();
	else
		ft_execve(exec);
	exit(1);
}

int	ft_execute_starter(void)
{
	t_executable	*exec;

	exec = g_global.exec;
	while (exec)
	{
		if (ft_execute_main(exec))
		{
			exec = exec->next;
			continue ;
		}
		exec->pid = fork();
		if (exec->pid == 0)
			ft_execute_chield(exec);  
		if (exec->pid == -1)
			return (0); //hata fork
		exec = exec->next;
	}
	ft_close_fd();
	exec = g_global.exec;
	while (exec)
	{
		if (exec->pid)
			waitpid(exec->pid, g_global.exit_status, 0);
		exec = exec->next;
	}
	return(1);
}
