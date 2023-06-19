/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:57:28 by havyilma          #+#    #+#             */
/*   Updated: 2023/06/19 20:26:48 by havyilma         ###   ########.fr       */
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
		if (input[i] >= 'a' && input[i] <= 'z' && -)
			total++;
		i++;
	}
	return (total);
}

int	ft_single

int	ft_len_u_space(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ')
		i++;
	i = 0;
	while(input[i] && input[i] != ' ')
		i++;
	return (i);
}

int	ft_print_cnf()
{
	printf("command not found\n");
}

int	ft_parser(char *input, struct ms *tdata)
{
	int	i;
	int	p;
	int	sp;
	int	cnt;
	tdata->command = malloc(sizeof(char) * ft_alphalen(input));
	sp = ft_len_u_space(input) - 1;
	i = 0;
	p = 0;
	while(input[i] && input[i] == ' ')
		i++;
	p = i;
	while (input[p])
	{
		if (input[p] && input[p] != ' ')
		{
			if (input[p] == 39 /*tek tırnak*/ && input[sp] == 39)
			{
				while (p < sp)
				{
					if (input[p] == 39 || input[p] == 34)
						return (0);
					p++;
				}
				p = i;
			}

			if (input[p] == 34 /*çift tırnak*/ && input[sp] == 34)
			{
				while (p < sp)
				{
					if (input[p] == 39 || input[p] == 34)
						return (0);
					p++;
				}
			}
			if ((input[i] >= 'a' && input[i] <= 'z') || input[i] == '-')
			{
				tdata->command[i++] = input[p];
				if()
			}
		}
	}
}

int	main(void)
{
	struct ms tdata;
	while (1)
	{
		char *input = readline("Minishell> ");
		if (!ft_parser(input, &tdata))
			return (1);
		printf("entered: %s\n", input);
		free(input);
	}
	return (0);
}