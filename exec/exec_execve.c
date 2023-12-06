/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:28:17 by mkoroglu          #+#    #+#             */
/*   Updated: 2023/08/24 18:06:19 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**ft_new_path(char *all_path, char *func)
{
	char	**path_options;
	char	*tmp;
	int		i;

	i = 0;
	if (!all_path)
		return (0);
	path_options = ft_split(all_path, ':');
	while (path_options[i])
	{
		if (path_options[i][ft_strlen(path_options[i]) - 1] != '/')
		{
			tmp = ft_strjoin(path_options[i], "/");
			if (path_options[i])
				free (path_options[i]);
			path_options[i] = tmp;
		}
		tmp = ft_strjoin(path_options[i], func);
		if (path_options[i])
			free (path_options[i]);
		path_options[i] = tmp;
		i++;
	}
	return (path_options);
}

static char	*ft_access_cont(char *all_paths, char *func)
{
	char	**path_options;
	char	*path;
	int		i;

	i = 0;
	path_options = ft_new_path(all_paths, func);
	if (!path_options)
		return (0);
	while (path_options[i])
	{
		if (!access(path_options[i], 0))
		{
			path = ft_strdup(path_options[i]);
			ft_free_double_pointer(path_options);
			return (path);
		}
		i++;
	}
	ft_free_double_pointer(path_options);
	dup2(g_global.stdout_control, 1);
	printf("minishell: %s: command not found\n", func);
	if (all_paths)
		free(all_paths);
	exit (127);
}

int	ft_execve(t_executable *exec)
{
	char	*path;

	if (!exec->str || !exec->str[0])
		return (0);
	if (ft_strchr(exec->str[0], '/') && access(exec->str[0], 0))
	{
		dup2(g_global.stdout_control, 1);
		printf("minishell: %s: No such file or directory\n", exec->str[0]);
		exit (127);
	}
	if (!access(exec->str[0], 0) && ft_strchr(exec->str[0], '/'))
		path = ft_strdup(exec->str[0]);
	else
		path = ft_access_cont(get_from_env("PATH"), exec->str[0]);
	if (!path)
	{
		dup2(g_global.stdout_control, 1);
		printf("minishell: %s: No such file or directory\n", exec->str[0]);
		exit(127);
	}
	execve(path, exec->str, g_global.envp);
	return (1);
}
