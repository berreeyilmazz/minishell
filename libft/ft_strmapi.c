/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 20:00:55 by mkoroglu          #+#    #+#             */
/*   Updated: 2022/11/10 19:45:10 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *str, char (*f)(unsigned int, char))
{
	char			*new_array;
	unsigned int	len_str;
	unsigned int	count;

	if (!str || !f)
		return (0);
	count = 0;
	len_str = ft_strlen(str);
	new_array = (char *)malloc(len_str + 1);
	if (!new_array)
		return (0);
	while (str[count])
	{
		new_array[count] = f(count, str[count]);
		count++;
	}
	new_array[count] = 0;
	return (new_array);
}
