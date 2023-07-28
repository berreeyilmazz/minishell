/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:35:47 by mkoroglu          #+#    #+#             */
/*   Updated: 2022/11/14 20:25:24 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *str, char const *set)
{
	unsigned int	start;
	unsigned int	end;

	if (!str)
		return (0);
	start = 0;
	end = ft_strlen(str);
	if (end == 0)
		return (ft_strdup(""));
	while (ft_strchr(set, *(str + start)) && str[start])
		start++;
	if (start == end)
		return (ft_strdup(""));
	while (end > 0 && ft_strchr(set, *(str + end - 1)))
		end--;
	return (ft_substr(str, start, (end - start)));
}
