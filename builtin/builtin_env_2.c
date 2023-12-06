/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 00:09:02 by havyilma          #+#    #+#             */
/*   Updated: 2023/08/24 21:26:53 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_back_env(char *str)
{
	t_env	*env;

	env = g_global.env;
	while (env->next)
		env = env->next;
	env->next = malloc(sizeof(t_env));
	env = env->next;
	env->line = ft_strdup(str);
	env->next = NULL;
}

void	add_back_exp(char *str, char flag)
{
	t_export	*exp;

	exp = g_global.exp;
	while (exp->next)
		exp = exp->next;
	exp->next = malloc(sizeof(t_export));
	exp = exp->next;
	if (flag == '=')
		exp->line = put_quotes(str);
	else
		exp->line = ft_strdup(str);
	exp->next = NULL;
}

char	*put_quotes(char *str)
{
	char	*new;
	int		n;
	int		s;

	n = 0;
	s = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + 3));
	while (str[s])
	{
		new[n] = str[s];
		if (str[s] == '=')
		{
			n++;
			new[n] = 34;
		}
		s++;
		n++;
	}
	new[n++] = 34;
	new[n] = '\0';
	return (new);
}

void	take_line(t_export **tmp, int i)
{
	char	*hey;

	hey = put_quotes(g_global.envp[i]);
	(*tmp)->line = ft_strdup(hey);
	free(hey);
}

void	take_str(t_export **tmp, char *str)
{
	if ((*tmp)->line)
		free((*tmp)->line);
	if (is_there_equal_sign(str) == '=')
		(*tmp)->line = put_quotes(str);
	else
		(*tmp)->line = ft_strdup(str);
}
