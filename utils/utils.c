/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:27:46 by mkoroglu          #+#    #+#             */
/*   Updated: 2023/08/25 13:56:17 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_zero_struct_executable(t_executable	*exec)
{
	exec->fd_input = 0;
	exec->fd_output = 1;
	exec->pid = 0;
	exec->next = NULL;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s2 || !s1)
		return (1);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strcmp_for_re(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	if (s1[i] == '=' || !s1[i])
		return (0);
	return (1);
}

void	ft_error_no_file(char *str)
{
	printf("minishell: %s: No such file or directory\n", str);
	g_global.signal_status = -1;
	g_global.exit_status = 1;
}

void	ft_wait_pid(void)
{
	t_executable	*exec;

	exec = g_global.exec;
	while (exec)
	{
		if (exec->pid)
		{
			waitpid(exec->pid, &g_global.exit_status, 0);
			if (WIFEXITED(g_global.exit_status))
				g_global.exit_status = WEXITSTATUS(g_global.exit_status);
		}
		exec = exec->next;
	}
}
