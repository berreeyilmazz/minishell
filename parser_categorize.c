/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_categorize.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:03:30 by havyilma          #+#    #+#             */
/*   Updated: 2023/07/27 01:11:42 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_if_red_pipe(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len == 1 && (str[0] == '|' || str[0] == '<' || str[0] == '>'))
		return(-1);
	if(len == 2 && ((str[0] == '|' || str[0] == '<' || str[0] == '>') 
		|| (str[1] == '|' || str[1] == '<' || str[1] == '>')))
		return (-1);
	return (0);
}

int	ft_get_type(void)
{
	t_token	*token;

	token = g_global.tokens;
	token->type = COMMAND;
	token = token->next;
	while (token != NULL)
	{
		if (token->type == FILENAME)
			token = token->next;
		if (token == NULL)
			return (0);
		ft_types(&token);
		if (token->type == PIPE)
		{
			if(token->next == NULL || (token->next != NULL && ft_if_red_pipe(token->next->content) == -1))
				return (ft_syntax_error());
			token = token->next;
			token->type = COMMAND;
		}
		else if (token->type == RED_I || token->type == DB_I
			|| token->type == RED_O || token->type == DB_O)
		{
			if(token->next == NULL || (token->next != NULL && ft_if_red_pipe(token->next->content) == -1))
				return (ft_syntax_error());
			token = token->next;
			token->type = FILENAME;
		}
		token = token->next;
	}
	return (1);
}

void	ft_types(t_token **token)
{
	if (!ft_strcmp((*token)->content, "|"))
		(*token)->type = PIPE;
	else if (!ft_strcmp((*token)->content, "<"))
		(*token)->type = RED_I;
	else if (!ft_strcmp((*token)->content, ">"))
		(*token)->type = RED_O;
	else if (!ft_strcmp((*token)->content, ">>"))
		(*token)->type = DB_O;
	else if (!ft_strcmp((*token)->content, "<<"))
		(*token)->type = DB_I;
	else if (!ft_strcmp((*token)->content, "$"))
		(*token)->type = DOLLAR;
	else
		(*token)->type = COMMAND;
}
