/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:57:28 by havyilma          #+#    #+#             */
/*   Updated: 2023/06/20 19:22:43 by havyilma         ###   ########.fr       */
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
//	int	rtrn;

	i = 0;
//	rtrn = 0;
	while (input[i] == ' ')
		i++;
	while(input[i] && input[i] != ' ')
	{
		i++;
//		rtrn++;
	}
	return (i);
}

int	ft_print_cnf()
{
	printf("command not found\n");
	return(0);
}

int	ft_parser(char *input, struct ms *tdata)
{
	int	i;
	int	p;
	int	sp;
	int indx;
	tdata->command = malloc(sizeof(char) * (ft_alphalen(input) - 1));
	sp = ft_len_u_space(input) - 1;
	indx = 0;
	i = 0;
	p = 0;
	while(input[p] == ' ')
	{
		p++;
		i++;
	}
	while (p < sp)
	{
		while ((input[p] >= 'a' && input[p] <= 'z') || input[p] == '-')
		{
			tdata->command[indx] = input[p];
			indx++;
			p++;
		}
		if (input[p] && input[p] != ' ')
		{
			if (input[i] == 39 && input[sp] == 39)
			{
				while (i < sp - 1)
				{
					if (!((input[i + 1] >= 'a' && input[i + 1] <= 'z') || (input[i + 1] == 34 || input[i + 1] == 39)))
					{
						printf("LANNN\n");
						return (0);
					}
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
			while (input[p] && ((input[p] >= 'a' && input[p] <= 'z') || input[p] == '-' || input[p] == 34 || input[p] == 39))
			{
				while(input[p] == 34 || input[p] == 39)
					p++;
				tdata->command[indx] = input[p];
				printf("    tdata->command[i]:%c\n", tdata->command[indx]);
				indx++;
				p++;
			}
		}
		p++;
	}
	return (1);
}
/*
int	main(void)
{
	struct ms tdata;
	while (1)
	{
		char *input = readline("Minishell> ");
		if(!ft_parser(input, &tdata))
		{
			free(input);
			return (ft_print_cnf());
		}
		printf("command: %s\n", tdata.command);
		free(input);
	}
	return (0);
}
*/