/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_categ.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:03:30 by havyilma          #+#    #+#             */
/*   Updated: 2023/07/05 17:11:56 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_categorize(struct ms *tdata)
{
	int	i;

	i = 0;
	tdata->flg = malloc(sizeof(char) * tdata->cnt);
	while (i < tdata->cnt)
	{
		if (ft_strcmp("echo", tdata->str[i]))
			tdata->flg[i] = 'e';
		else if (ft_strcmp("ls", tdata->str[i]))
			tdata->flg[i] = 'l';
		else if (ft_strcmp("cat",))
		i++;
	}
}