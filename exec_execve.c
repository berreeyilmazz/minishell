/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:28:17 by mkoroglu          #+#    #+#             */
/*   Updated: 2023/07/28 03:39:38 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	write(2, "command not found\n", 18);
	return (0);
}

//hata mesajı nasıl olmalı?
int	ft_execve(t_executable *exec)
{
	char	*path;

	path = ft_access_cont(ft_find_in_env("PATH="), exec->str[0]); //PATH ksımını sonunda nulla at

	if (!path)
		exit(127);
	execve(path, exec->str, g_global.env); //burada exit atmasam nıolur? -1 hatası kaldı
	return (1);
}
