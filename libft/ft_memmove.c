/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:26:54 by mkoroglu          #+#    #+#             */
/*   Updated: 2022/11/17 10:43:52 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	if (src < dest && (size_t)(dest) < count + (size_t)src)
	{
		while (0 < count)
		{
			count--;
			*(char *)(dest + count) = *(char *)(src + count);
		}
	}
	else
		return (ft_memcpy(dest, src, count));
	return (dest);
}
