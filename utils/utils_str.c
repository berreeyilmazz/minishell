/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:28:40 by mkoroglu          #+#    #+#             */
/*   Updated: 2023/08/25 14:17:45 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_find_in_env(char *str)
{
	char	*line;
	int		i;
	int		a;

	a = 0;
	i = 0;
	while (g_global.envp[i])
	{
		if (!ft_strncmp(g_global.envp[i], str, ft_strlen(str)))
			break ;
		i++;
		if (!g_global.envp[i])
			return (0);
	}
	while (g_global.envp[i][a] && g_global.envp[i][a] != '\n')
		a++;
	line = malloc(sizeof(char) * (a));
	if (!line)
		return (0);
	ft_strlcpy(line, &g_global.envp[i][ft_strlen(str)], a + 1);
	return (line);
}

void	ft_free_double_pointer(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	else if (!*str)
	{
		free (str);
		return ;
	}
	while (str[i])
	{
		if (str[i])
			free (str[i]);
		i++;
	}
	if (str)
		free(str);
}

char	*ft_strjoin_vol2(char const *s1, char const *s2)
{
	char	*thegoodplace;
	int		i;
	int		k;

	if (!s1 || !s2)
		return (NULL);
	thegoodplace = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (thegoodplace == 0)
		return (0);
	i = 0;
	k = 0;
	while (s1[k])
		thegoodplace[i++] = s1[k++];
	thegoodplace[i++] = ' ';
	k = 0;
	while (s2[k])
		thegoodplace[i++] = s2[k++];
	thegoodplace[i] = '\0';
	return (thegoodplace);
}

int	ft_check_if_next(int i, t_token **token)
{
	int	ctrl;

	ctrl = 0;
	while (g_global.input[i])
	{
		if (g_global.input[i] && g_global.input[i] != 32)
		{
			ctrl = 1;
			break ;
		}
		i++;
	}
	if ((*token)->content == NULL && ctrl == 0)
	{
		(*token)->next = NULL;
		return (0);
	}
	if (ctrl == 1 && (*token)->content == NULL)
		return (0);
	if (ctrl == 1 && (*token)->content != NULL)
		return (1);
	(*token)->next = NULL;
	return (0);
}
