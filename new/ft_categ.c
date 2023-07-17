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

void	ft_categorize(t_token *came)
{
	if (ft_strcmp(came->content, "|"))
		came->type = 4;
	else if (ft_strcmp(came->content, ">"))
	{
		came->type = 1;
		came->next->type = 100;
	}
	else if(ft_strcmp(came->content, "<"))
	{
		came->type = 2;
	//?	came->next->type = OUTPUT;
	}
	else if(ft_strcmp(came->content, ">>"))
		came->type = 3;
	else if(ft_strcmp(came->content, "<<"))
		came->type = 4;
	else if (ft_strcmp(came->content, "$"))
		came->type = 5;
	/*else if (ft_strcmp(came->content, ""))
		came->type = OUTPUT;*/
	else
		came->type = 6;
}
