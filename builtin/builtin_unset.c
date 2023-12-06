/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:13:12 by havyilma          #+#    #+#             */
/*   Updated: 2023/08/25 01:31:22 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	delete_exp_when_middle(char *str, t_export **exp)
{
	t_export	*new_next;

	while ((*exp)->next->next)
	{
		if (ft_strcmp((*exp)->next->line, str) == '=' 
			|| ft_strcmp((*exp)->line, str) == 0)
		{
			new_next = (*exp)->next->next;
			if ((*exp)->next->line)
				free((*exp)->next->line);
			if ((*exp)->next)
				free((*exp)->next);
			(*exp)->next = new_next;
			return (1);
		}
		(*exp) = (*exp)->next;
	}
	return (0);
}

int	delete_identifier_exp(char *str)
{
	t_export	*exp;

	exp = g_global.exp;
	if (ft_strcmp(exp->line, str) == '=' || ft_strcmp(exp->line, str) == 0)
	{
		free(exp->line);
		g_global.exp = exp->next;
		free(exp);
		return (0);
	}
	if (delete_exp_when_middle(str, &exp))
		return (0);
	if (exp && exp->next && !exp->next->next)
	{
		if (ft_strcmp(exp->next->line, str) == '='
			|| !ft_strcmp(exp->next->line, str))
		{
			free (exp->next->line);
			free (exp->next);
			exp->next = NULL;
		}
	}
	return (0);
}

int	delete_env_when_middle(char *str, t_env **env)
{
	t_env	*new_next;

	while ((*env)->next->next)
	{
		if (ft_strcmp((*env)->next->line, str) == '=')
		{
			new_next = (*env)->next->next;
			free((*env)->next->line);
			free((*env)->next);
			(*env)->next = new_next;
			return (1);
		}
		(*env) = (*env)->next;
	}
	return (0);
}

int	delete_identifier_env(char *str)
{
	t_env	*env;

	env = g_global.env;
	if (ft_strcmp(env->line, str) == '=')
	{
		free(env->line);
		g_global.env = env->next;
		free(env);
		return (0);
	}
	if (delete_env_when_middle(str, &env))
		return (0);
	if (env && env->next && !env->next->next)
	{
		if (ft_strcmp(env->next->line, str) == '=')
		{
			free(env->next->line);
			free(env->next);
			env->next = NULL;
		}
	}
	return (0);
}

void	ft_unset(t_executable *exec)
{
	int	i;

	i = 1;
	if (g_global.pipe_cnt > 0)
		return ;
	while (exec->str[i])
	{
		if (exec->str[i][0] >= 48 && exec->str[i][0] <= 57)
		{
			printf("export: '%s': not a valid identifier\n", exec->str[i]);
			i++;
			continue ;
		}
		delete_identifier_exp(exec->str[i]);
		delete_identifier_env(exec->str[i]);
		i++;
	}
}
