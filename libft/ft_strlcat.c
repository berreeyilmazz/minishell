/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:31:04 by mkoroglu          #+#    #+#             */
/*   Updated: 2022/11/14 16:55:20 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	len_src;
	size_t	len_dest;
	size_t	i;

	if (!dstsize && !dest)
		return (0);
	i = 0;
	len_src = ft_strlen(src);
	len_dest = ft_strlen(dest);
	if (dstsize <= len_dest)
		return (len_src + dstsize);
	while (dstsize > len_dest + i + 1 && src[i])
	{
		dest[len_dest + i] = src[i];
		i++;
	}
	if (dstsize > len_dest + i)
		dest[len_dest + i] = '\0';
	return (len_dest + len_src);
}
