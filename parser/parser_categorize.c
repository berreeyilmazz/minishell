/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_categorize.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:03:30 by havyilma          #+#    #+#             */
/*   Updated: 2023/08/25 01:24:25 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_if_red_pipe(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len == 1 && (str[0] == '<' || str[0] == '>'))
		return (-1);
	if (len == 1 && str[0] == '|')
		return (-2);
	if (len == 2 && ((str[0] == '<' || str[0] == '>') 
			&& (str[1] == '<' || str[1] == '>')))
		return (-1);
	return (0);
}

int	ft_check_content(t_token **token, char *str)
{
	if (ft_if_red_pipe(str))
		(*token)->type = COMMAND;
	return (0);
}

int	ft_types(t_token **token)
{
	if ((*token)->content == NULL)
	{
		(*token)->type = 5;
		return (0);
	}
	if ((*token)->type != 0)
		return (0);
	if (!ft_strcmp((*token)->content, "<"))
		(*token)->type = RED_I;
	else if (!ft_strcmp((*token)->content, "|"))
		(*token)->type = PIPE;
	else if (!ft_strcmp((*token)->content, ">"))
		(*token)->type = RED_O;
	else if (!ft_strcmp((*token)->content, ">>"))
		(*token)->type = DB_O;
	else if (!ft_strcmp((*token)->content, "<<"))
		(*token)->type = DB_I;
	else
		(*token)->type = COMMAND;
	return (0);
}

int	after_red_pipe(t_token **token)
{
	if ((*token)->next == NULL)
		return (0);
	if ((*token)->type == PIPE)
	{
		if ((*token)->next == NULL || ((*token)->next != NULL 
				&& ft_if_red_pipe((*token)->next->content) == -2))
			return (ft_syntax_error());
		if (ft_if_red_pipe((*token)->next->content) == -1)
			return (1);
		(*token) = (*token)->next;
		(*token)->type = COMMAND;
	}
	else if ((*token)->type == RED_I || (*token)->type == DB_I 
		|| (*token)->type == RED_O || (*token)->type == DB_O)
	{
		if ((*token)->next == NULL || ((*token)->next != NULL 
				&& (ft_if_red_pipe((*token)->next->content) != 0)))
			return (ft_syntax_error());
		(*token) = (*token)->next;
		(*token)->type = FILENAME;
	}
	return (0);
}

int	ft_get_type(void)
{
	t_token	*token;
	int		c;

	token = g_global.tokens;
	if (token->content == NULL)
		return (ft_print_cnf());
	while (token != NULL)
	{
		ft_types(&token);
		c = after_red_pipe (&token);
		if (c == -1)
			return (-1);
		if (token->next)
			token = token->next;
		else
			return (0);
	}
	return (0);
}
