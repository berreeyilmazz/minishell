/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 10:30:25 by havyilma          #+#    #+#             */
/*   Updated: 2023/08/25 14:01:05 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	eof_control_heredoc(char *line)
{
	if (!line)
	{
		write(1, "\033[2D", 4);
		write(1, "\033[0m", 5);
		g_global.exit_status = 0;
		exit(0);
	}
}

void	eof_control_main(char *line)
{
	if (!line)
	{
		write(1, "\033[2D", 4);
		write(1, "\033[0mexit\n", 9);
		g_global.exit_status = 0;
		exit(0);
	}
}

void	ft_sig_chield(int sig)
{
	(void)sig;
	dup2(g_global.stdout_control, 1);
	printf("\n");
	exit (1);
}

void	ft_sig_main(int sig)
{
	(void)sig;
	g_global.exit_status = 1;
	g_global.signal_status = -1;
	if (g_global.heredoc_pid > 0)
	{
		kill(g_global.heredoc_pid, SIGUSR1);
		return ;
	}
	write(1, "\033[A", 3);
	ioctl(0, TIOCSTI, "\n");
}

void	signal_handler(void)
{
	signal(SIGINT, ft_sig_main);
	signal(SIGQUIT, SIG_IGN);
}
