/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:26:05 by havyilma          #+#    #+#             */
/*   Updated: 2023/07/28 08:49:52 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	int	i;

	(void)ac;
	(void)av;
	i = 0;
	get_env(envp);   // her readline çalıştığında güncellenecek mi??
	get_line();
	return (0);
}

void	get_env(char **envp)
{
	int	i;
	int	cnt;
	
	cnt = 0;
	i = 0;
	while(envp[cnt])
		cnt++;
	g_global.env = malloc(sizeof(char *) * cnt + 1);
	while (i < cnt)
	{
		g_global.env[i] = ft_strdup(envp[i]);
		i++;
	}
	g_global.env[i] = NULL;
}

void yazdir_t_token(void)
{
	t_token *iter;
	iter = g_global.tokens;

	while (iter)
	{
	//	printf("\n-Yeni Token-\n");
		printf("Type = %u, Contents-> [%s]\n",iter->type, iter->content);
		iter = iter->next;
	}
	fflush(stdout);
}
void	get_line(void)
{
	while (1)
	{
		ft_init();
		g_global.input = readline("Minishell> ");
		add_history(g_global.input);
		if(g_global.input[0] == '\n')
		{
			free(g_global.input);
			continue;
		}
		if (ft_get_tokens(-1, 0) == -1)
		{
			ft_free();
			return ;
		}
		if (ft_get_type() == -1)
		{
			ft_free();
			continue;
		}		
		ft_setting_t_executable(); // hata kontrol eklemesi.
	//	yazdir_t_token();
		//yazdir_t_executable();
		ft_execute_starter();
	//	system("leaks minishell");
		//printf("fdsfasdfs\n");
	}
}
