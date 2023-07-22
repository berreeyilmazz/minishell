/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:18:19 by havyilma          #+#    #+#             */
/*   Updated: 2023/07/08 15:05:09 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}
char	*ft_strdup(const char *s1)
{
	char	*temp;
	int		length;
	int		i;

	i = 0;
	length = ft_strlen(s1);
	temp = malloc(sizeof(char) * (length + 1));
	if (!temp)
		return (NULL);
	while (s1 && s1[i])
	{
		temp[i] = s1[i];
		i++;
	}
	temp[i] = 0;
	return (temp);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	/*if (s1[i] != '\0' && s2[i] != '\0')
		return (1);*/
	return (s1[i] - s2[i]);
}
