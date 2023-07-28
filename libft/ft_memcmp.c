/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:49:27 by mkoroglu          #+#    #+#             */
/*   Updated: 2022/11/10 17:52:44 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *buf1, const void *buf2, size_t count)
{
	size_t			i;
	unsigned char	*c_buf1;
	unsigned char	*c_buf2;

	c_buf1 = (unsigned char *)buf1;
	c_buf2 = (unsigned char *)buf2;
	i = 0;
	if (count == 0)
		return (0);
	while (c_buf1[i] == c_buf2[i] && i + 1 < count)
		i++;
	return (c_buf1[i] - c_buf2[i]);
}
