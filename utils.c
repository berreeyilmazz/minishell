/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:27:46 by mkoroglu          #+#    #+#             */
/*   Updated: 2023/07/30 01:16:49 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_zero_struct_executable(t_executable	*exec)
{
	exec->fd_input = 0;
	exec->fd_output = 1;
	exec->pid = 0;
	exec->next = NULL;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	if(!s2[i])
		return (1);
	else
		return (0);
}
