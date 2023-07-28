/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:46:04 by mkoroglu          #+#    #+#             */
/*   Updated: 2022/11/17 14:08:19 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *buf, int c, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		if (*(unsigned char *)(buf + i) == (unsigned char)c)
			return ((void *)(buf + i));
		i++;
	}
	return (0);
}
