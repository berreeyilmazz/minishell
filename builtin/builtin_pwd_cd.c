/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 03:43:11 by havyilma          #+#    #+#             */
/*   Updated: 2023/08/23 02:50:07 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(void)
{
	char	path[1024];

	if (getcwd(path, sizeof(path)) != NULL)
		printf ("%s\n", path);
	else
	{
		dup2(g_global.stdout_control, 1);
		printf ("pwd: cannot access: No such file or directory\n");
	}
}

void	change_oldpwd_env(char *old_loc, char *new_loc)
{
	t_env		*env;

	env = g_global.env;
	while (env)
	{
		if (ft_strcmp(env->line, "OLDPWD") == '=')
		{
			free(env->line);
			env->line = ft_strjoin("OLDPWD=", old_loc);
		}
		else if (ft_strcmp(env->line, "PWD") == '=')
		{
			free(env->line);
			env->line = ft_strjoin("PWD=", new_loc);
		}
		env = env->next;
	}
}

void	change_oldpwd(char *old_loc, char *new_loc)
{
	t_export	*exp;
	char		*tmp;

	exp = g_global.exp;
	change_oldpwd_env(old_loc, new_loc);
	while (exp)
	{
		if (ft_strcmp(exp->line, "OLDPWD") == '=')
		{
			free(exp->line);
			tmp = ft_strjoin("OLDPWD=", old_loc);
			exp->line = put_quotes(tmp);
			free(tmp);
		}
		else if (ft_strcmp(exp->line, "PWD") == '=')
		{
			free(exp->line);
			tmp = ft_strjoin("PWD=", new_loc);
			exp->line = put_quotes(tmp);
			free(tmp);
		}
		exp = exp->next;
	}
}
