/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 21:18:57 by mkoroglu          #+#    #+#             */
/*   Updated: 2022/11/17 14:08:39 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new_malloc;
	size_t	lenght_s;

	lenght_s = ft_strlen(s);
	new_malloc = (char *)malloc(lenght_s + 1);
	if (!new_malloc)
		return (0);
	new_malloc[lenght_s] = 0;
	while (lenght_s > 0)
	{
		lenght_s--;
		new_malloc[lenght_s] = s[lenght_s];
	}
	return (new_malloc);
}
