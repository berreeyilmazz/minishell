/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:47:35 by mkoroglu          #+#    #+#             */
/*   Updated: 2022/10/06 18:23:47 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int arg)
{
	if (('a' <= arg && arg <= 'z') || ('A' <= arg && arg <= 'Z'))
		return (1);
	return (0);
}