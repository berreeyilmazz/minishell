/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:52:41 by mkoroglu          #+#    #+#             */
/*   Updated: 2022/11/17 01:14:42 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*iter;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		iter = (*lst)->next;
		ft_lstdelone(*lst, del);
		(*lst) = iter;
	}
}
