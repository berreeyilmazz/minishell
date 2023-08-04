/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:09:47 by mkoroglu          #+#    #+#             */
/*   Updated: 2022/11/17 10:57:15 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_transfer(char *dest, char const *str, unsigned int d_adres)
{
	int	i;

	i = 0;
	while (str[i])
	{
		dest[d_adres + i] = str[i];
		i++;
	}
	dest[d_adres + i] = 0;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	int		len_s1;
	int		len_s2;

	if (!s1 || !s2)
		return (0);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	new_str = (char *)malloc(len_s1 + len_s2 + 1);
	if (!new_str)
		return (0);
	ft_transfer(new_str, s1, 0);
	ft_transfer(new_str, s2, len_s1);
	return (new_str);
}
