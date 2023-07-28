/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yazdirmafonksiyonları.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 00:33:22 by mkoroglu          #+#    #+#             */
/*   Updated: 2023/07/27 00:38:45 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

void yazdir_t_token(void)
{
	t_token *iter;
	iter = g_global.tokens;

	while (iter)
	{
		printf("\n-Yeni Token-\n");
		printf("Type = %u, Contents-> %s\n",iter->type, iter->content);
		iter = iter->next;
	}
	fflush(stdout);
}

void yazdir_t_executable(void)
{
	t_executable *iter;
	iter = g_global.exec;
		int i ;
	while (iter)
	{
		printf("\n-Yeni exec-\n");
		printf("fd_input = %d, fd_output = %d, pid = %d, STR->\n", iter->fd_input, iter->fd_output, iter->pid);
		i = 0;
		while (iter->str[i])
		{
			printf("%s", iter->str[i]);
			i++;
		}
		iter = iter->next;
	}
	fflush(stdout);
}