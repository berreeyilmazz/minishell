/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:53:16 by mkoroglu          #+#    #+#             */
/*   Updated: 2023/07/10 20:49:41 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i_h;
	size_t	i_n; 

	i_h = 0;
	if (!len && !haystack)
		return (NULL);
	if (!needle[0] || !needle)
		return ((char *)haystack);
	while (i_h < len && haystack[i_h])
	{
		i_n = 0;
		while ((haystack[i_h + i_n] == needle[i_n])
			&& haystack[i_h + i_n] && (i_h + i_n) < len)
		{
			i_n++;
			if (!needle[i_n])
				return ((char *)(haystack + i_h));
		}
		i_h++;
	}
	return (0);
}
