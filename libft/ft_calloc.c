/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 21:12:51 by mkoroglu          #+#    #+#             */
/*   Updated: 2022/11/10 17:43:31 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*new_calloc;

	if (count > 0 && size > 0 && (size > SIZE_MAX / count))
		return (0);
	new_calloc = malloc(count * size);
	if (!new_calloc)
		return (0);
	ft_bzero(new_calloc, (count * size));
	return (new_calloc);
}
