/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:26:05 by havyilma          #+#    #+#             */
/*   Updated: 2023/07/08 02:00:28 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init()
{
		g_global.tokens = malloc(sizeof(t_token));
		g_global.cnt = 0;
		g_global.pipe_cnt = 0;
}

void	ft_free()
{
	t_token	*token;
	t_token *tmp;

	token = g_global.tokens;
	while(token)
	{
		tmp = token->next;
		free(token->content);
		free(token);
		token = tmp;
	}

	free(g_global.input);
	g_global.tokens = NULL;
	g_global.input = NULL;
	g_global.cnt = 0;
	g_global.pipe_cnt = 0;
}


void write_global(){
	t_token		*tmp;

	tmp = g_global.tokens;
	while (tmp)
	{
		if (tmp->next ==  NULL){
			printf("=> [%s]\n", tmp->content);
			break;
			return ;
		}
		else{
			printf("-> [%s]\n", tmp->content);
			tmp = tmp->next;

		}
	}
}

void	get_line()
{
	int	i;
	t_token *tmp;

	tmp = g_global.tokens;

	i = 0;
	while (i < 2)
	{
		g_global.input = readline("Minishell> ");
		ft_init();
		ft_counter_word(g_global.input);
		ft_get_tokens(-1, 0);
		write_global();
		ft_free();
		i++;
	}

}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	int i;

	i = 0;
	get_line();
    system("leaks minishell");
	return (0);
}

