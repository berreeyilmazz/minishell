/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:34:41 by mkoroglu          #+#    #+#             */
/*   Updated: 2022/10/06 18:37:10 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int arg)
{
	if (('a' <= arg && arg <= 'z') || ('A' <= arg && arg <= 'Z'))
		return (1);
	else if ('0' <= arg && arg <= '9')
		return (1);
	return (0);
}
