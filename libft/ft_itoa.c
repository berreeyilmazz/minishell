/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:39:07 by mkoroglu          #+#    #+#             */
/*   Updated: 2022/10/12 19:08:10 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_new_array(int n, int count, int negative)
{
	char	*new_array;

	new_array = (char *)malloc(count + 1);
	if (!new_array)
		return (0);
	new_array[count] = 0;
	while (count > 0)
	{
		count--;
		new_array[count] = (n % 10) * negative + '0';
		n /= 10;
	}
	if (negative == -1)
		new_array[0] = '-';
	return (new_array);
}

char	*ft_itoa(int n)
{
	int		n_spare;
	int		count;
	int		negative;

	n_spare = n;
	count = 1;
	negative = 1;
	if (n < 0)
	{
		negative = -1;
		count++;
	}
	while (n_spare <= -10 || 10 <= n_spare)
	{
		n_spare /= 10;
		count++;
	}
	return (ft_new_array(n, count, negative));
}
