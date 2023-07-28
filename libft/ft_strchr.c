/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:37:53 by mkoroglu          #+#    #+#             */
/*   Updated: 2022/11/17 14:08:32 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *string, int c)
{
	size_t	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == (char)c)
			return ((char *)(string + i));
		i++;
	}
	if (c == 0)
		return ((char *)(string + i));
	return (0);
}
