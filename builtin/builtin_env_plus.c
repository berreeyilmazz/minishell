/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_plus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 00:10:57 by havyilma          #+#    #+#             */
/*   Updated: 2023/08/25 04:14:10 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export_plus(t_executable *exec)
{
	int	i;

	i = 1;
	if (g_global.pipe_cnt > 0)
		return (0);
	while (exec->str[i])
	{
		if (!((exec->str[i][0] >= 97 && exec->str[i][0] <= 122)
			|| (exec->str[i][0] >= 65 && exec->str[i][0] <= 90)
			|| exec->str[i][0] == '_') || check_minus(exec->str[i]))
		{
			printf("minishell: export: '%s': not a valid identifier\n",
				exec->str[i]);
			i++;
			g_global.exit_status = 1;
			continue ;
		}
		re_fill_exp(exec->str[i]);
		if (is_there_equal_sign(exec->str[i]) == '=')
			re_fill_env(exec->str[i]);
		i++;
	}
	return (0);
}

char	is_there_equal_sign(char *str)
{
	int		i;
	char	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '=')
			flag = '=';
		i++;
	}
	i = 0;
	return (flag);
}

void	re_fill_exp_plus(t_export **old_exp, char *str)
{
	if ((*old_exp)->line)
		free ((*old_exp)->line);
	if (is_there_equal_sign(str) == '=')
		(*old_exp)->line = put_quotes(str);
	else
		(*old_exp)->line = ft_strdup(str);
}

void	re_fill_exp(char *str)
{
	t_export	*old_exp;
	int			i;
	int			d;

	old_exp = g_global.exp;
	while (old_exp)
	{
		i = 0;
		d = 0;
		while ((old_exp->line && str[i]) && old_exp->line[d] == str[i] 
			&& old_exp->line[d] != '=')
		{
			i++;
			d++;
		}
		if (old_exp->line && (!old_exp->line[d] && str[i] == '='))
		{
			re_fill_exp_plus(&old_exp, str);
			return ;
		}
		else if (old_exp->line[d] == '=' && !str[i])
			return ;
		old_exp = old_exp->next;
	}
	add_back_exp(str, is_there_equal_sign(str));
}

void	re_fill_env(char *str)
{
	t_env	*old_env;
	int		i;
	int		d;

	old_env = g_global.env;
	while (old_env)
	{
		i = 0;
		d = 0;
		while (old_env->line[d] == str[i] && old_env->line[d] != '=')
		{
			i++;
			d++;
		}
		if ((old_env->line[d] == str[i]) || (!old_env->line[d] || !str[i]))
		{
			free(old_env->line);
			old_env->line = ft_strdup(str);
			return ;
		}
		old_env = old_env->next;
	}
	add_back_env(str);
}
