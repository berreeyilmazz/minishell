/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_starter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 19:31:27 by mkoroglu          #+#    #+#             */
/*   Updated: 2023/08/02 09:25:25 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_execute_main(t_executable *exec)
{
	if (g_global.pipe_cnt > 0)
		return (0); //Buna çalışan dosyada bakman lazım.
	if (!ft_strncmp(exec->str[0], "cd", 2))//buralarda elle sayı falan da girdik bok gibi oldu
		ft_cd(exec);
	else if (!ft_strncmp(exec->str[0], "exit", 4))
		ft_exit(exec);
	/*else if (!ft_strncmp(exec->str[0], "export", 6) && exec->str[1]); //tek karakterse veriyor.
	else if (!ft_strncmp(exec->str[0], "unset", 5));
	else
		return (0);*/
	return (0);
}
//hatalardan ötürü retrn ihtiyacı duaybilir.
int	ft_execute_chield(t_executable *exec)
{  
	dup2(exec->fd_input, 0);
	dup2(exec->fd_output, 1);
	ft_close_fd();
	if (!ft_strncmp(exec->str[0], "echo", 4))
		ft_echo(exec);
	else if (!ft_strncmp(exec->str[0], "pwd", 3))
		ft_pwd();
	//else if (!ft_strncmp(exec->str[0], "export", 6));
	else if (!ft_strncmp(exec->str[0], "env", 3))
		ft_env();
	else
		ft_execve(exec);
	exit(1);
//	return(0);
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
