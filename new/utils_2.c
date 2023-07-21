/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:57:28 by havyilma          #+#    #+#             */
/*   Updated: 2023/07/08 02:06:54 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_alphalen(char *input)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (input[i])
	{
		if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] == '-'))
			total++;
		i++;
	}
	return (total);
}

int	ft_len_u_space(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ')
		i++;
	while(input[i] && input[i] != ' ')
		i++;
	return (i);
}

int	ft_print_cnf()
{
	printf("command not found\n");
	return(0);
}

int	ft_parser(char *input)
{
	int	i;
	int	p;
	int	sp;
	int indx;
	sp = ft_len_u_space(input) - 1;
	printf("++++ %d\n", sp);
	indx = 0;
	i = 0;
	p = 0;
	while(input[p] == ' ')
	{
		p++;
		i++;
	}
	while (p <= sp)
	{
		if (input[p] && input[p] != ' ')
		{
			if (input[i] == 39 && input[sp] == 39)
			{
				while (i < sp - 1)
				{
					if (!((input[i + 1] >= 'a' && input[i + 1] <= 'z') || (input[i + 1] == 34 || input[i + 1] == 39)))
						return (0);
					i++;
				}
			}
			else if (input[i] == 34 && input[sp] == 34)
			{
				while (i < sp - 1)
				{
					if (!((input[i + 1] >= 'a' && input[i + 1] <= 'z') || (input[i + 1] == 34 || input[i + 1] == 39)))
						return (0);
					i++;
				}
			}
			while (input[p] && (input[p] == '-' || input[p] == 34 || input[p] == 39))
			{
				while(input[p] == 34 || input[p] == 39)
					p++;
				tdata->context[indx] = input[p];
				indx++;
				p++;
			}
		}
		p++;
	}
	return (1);
}
