/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_categ.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:03:30 by havyilma          #+#    #+#             */
/*   Updated: 2023/07/07 22:18:18 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_type()
{
	int		i;
	t_token	*token;

	i = 0;
	token = g_global.tokens;
	token->type = COMMAND;
	if (token->next)
		token = token->next;
	else
		return;
	while(token)
	{
		ft_types(&token);
		if(token->type == PIPE)
		{
			token = token->next;
			token->type = COMMAND;
		}
		else if (token->type == RED_I || token->type == DB_I || token->type == RED_O || token->type == DB_O)
		{
			token = token->next;
			token->type = FILENAME;
		}
		if (token->next != NULL)
			token = token->next;
		else
			return;
	}
}

void	ft_types(t_token **token)
{
	if (!ft_strcmp((*token)->content, "|"))
		(*token)->type = PIPE;
	else if (!ft_strcmp((*token)->content, ">"))
		(*token)->type = RED_O;
	else if(!ft_strcmp((*token)->content, "<"))
		(*token)->type = RED_I;
	else if(!ft_strcmp((*token)->content, ">>"))
		(*token)->type = DB_O;
	else if(!ft_strcmp((*token)->content, "<<"))
		(*token)->type = DB_I;
	else if (!ft_strcmp((*token)->content, "$"))
		(*token)->type = DOLLAR;
	else
		(*token)->type = FILENAME;

}