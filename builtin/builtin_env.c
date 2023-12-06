/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 09:06:34 by havyilma          #+#    #+#             */
/*   Updated: 2023/08/24 20:51:17 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_env(void)
{
	t_env	*env;
	int		i;

	i = -1;
	g_global.env = malloc(sizeof(t_env));
	env = g_global.env;
	i = -1;
	while (g_global.envp[++i] != NULL)
	{
		env->line = ft_strdup(g_global.envp[i]);
		if (!g_global.envp[i + 1])
			break ;
		env->next = malloc(sizeof(t_env));
		env = env->next;
	}
	env->next = NULL;
}

void	fill_env_exp(void)
{
	int			i;
	t_export	*exp;

	fill_env();
	g_global.exp = malloc(sizeof(t_export));
	exp = g_global.exp;
	i = -1;
	while (g_global.envp[++i] != NULL)
	{
		take_line(&exp, i);
		if (!g_global.envp[i + 1])
			break ;
		exp->next = malloc(sizeof(t_export));
		exp = exp->next;
	}
	exp->next = NULL;
}

void	ft_env(void)
{
	t_env	*env;

	env = g_global.env;
	while (env)
	{
		printf("%s\n", env->line);
		if (env->next == NULL)
			return ;
		env = env->next;
	}
}

void	ft_export(void)
{
	t_export	*tmp;

	tmp = g_global.exp;
	while (tmp && tmp->line != NULL)
	{
		printf("declare -x %s\n", tmp->line);
		if (tmp->next == NULL)
			return ;
		tmp = tmp->next;
	}
}
