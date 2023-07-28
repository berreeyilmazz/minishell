/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 21:06:59 by mkoroglu          #+#    #+#             */
/*   Updated: 2022/11/12 17:43:24 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	size_t			i;
	long long int	number;
	long long int	negative;

	i = 0;
	number = 0;
	negative = 1;
	while (str[i] == ' ' || (9 <= str[i] && str[i] <= 13))
		i++;
	if (str[i] == '-')
		negative = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while ('0' <= str[i] && str[i] <= '9')
	{
		number *= 10;
		number += (str[i] - '0') * negative;
		if (number > 2147483647)
			return (-1);
		if (number < -2147483648)
			return (0);
		i++;
	}
	return ((int )(number));
}
