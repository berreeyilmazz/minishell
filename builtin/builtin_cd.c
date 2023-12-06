/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 02:49:19 by havyilma          #+#    #+#             */
/*   Updated: 2023/08/25 13:07:55 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_chdir(char *old_loc, char *new_loc, char *if_not)
{
	if (access(new_loc, 0))
	{
		g_global.exit_status = 1;
		printf("Minishell : %s : No such file or directory\n", if_not);
	}
	else if (g_global.pipe_cnt == 0 && chdir(new_loc) != -1)
		change_oldpwd(old_loc, new_loc);
	return (0);
}

int	go_to_home(char *now)
{
	char	*home;

	home = get_from_env("HOME");
	if (home == NULL)
	{
		printf("Minishell : cd: HOME not set\n");
		g_global.exit_status = 1;
		return (0);
	}
	print_chdir(now, home, NULL);
	free (home);
	return (0);
}

int	go_to_prev(char *old_path)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (old_path[i])
		i++;
	i--;
	while (old_path[i] != '/')
		i--;
	i++;
	new = malloc(sizeof(char) * (i + 1));
	if (i != 1)
		i--;
	while (j != i)
	{
		new[j] = old_path[j];
		j++;
	}
	print_chdir(old_path, new, NULL);
	free (new);
	return (0);
}

int	ft_cd(t_executable *exec)
{
	char	path_now[1024];
	char	*new;
	char	*new2;

	getcwd(path_now, sizeof(path_now));
	if (!exec->str[1] || !ft_strncmp(exec->str[1], "~", 1))
		return (go_to_home(path_now));
	if (exec->str[1][0] == '/')
		return (print_chdir(path_now, exec->str[1], exec->str[1]));
	if (exec->str[1][0] == '.' && exec->str[1][1] == '.')
		return (go_to_prev(path_now));
	new = ft_strjoin(path_now, "/");
	new2 = ft_strjoin(new, exec->str[1]);
	print_chdir(path_now, new2, exec->str[1]);
	free(new);
	free(new2);
	return (0);
}

int	check_minus(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (str[i] == '-')
			return (1);
		i++;
	}
	return (0);
}
