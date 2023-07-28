/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:57:48 by mkoroglu          #+#    #+#             */
/*   Updated: 2022/11/14 20:08:24 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char			*new_str;
	size_t			i;
	size_t			len_str;

	if (!str)
		return (0);
	i = 0;
	len_str = ft_strlen(str);
	if (len + start > len_str)
		len = len_str - start;
	if (start >= len_str)
		len = 0;
	new_str = (char *)malloc(len + 1);
	if (!new_str)
		return (0);
	while (str[start + i] && i < len)
	{
		new_str[i] = str[start + i];
		i++;
	}
	new_str[i] = 0;
	return (new_str);
}
