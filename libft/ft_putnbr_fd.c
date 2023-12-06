/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 02:31:23 by mkoroglu          #+#    #+#             */
/*   Updated: 2022/11/10 20:12:39 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_nmb_write(int n, int fd)
{
	if (-9 <= n && n <= 9)
	{
		if (n < 0)
			n *= -1;
		n += '0';
		write(fd, &n, 1);
	}
	else
	{
		ft_nmb_write((n / 10), fd);
		ft_nmb_write((n % 10), fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
		write(fd, "-", 1);
	ft_nmb_write(n, fd);
}
