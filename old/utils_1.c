/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:03:36 by havyilma          #+#    #+#             */
/*   Updated: 2023/07/05 17:06:01 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_words(char *str, int i, int j)
{
	char	*new;
	int		k;

	k = 0;
	new = malloc(sizeof(char) * (j - i + 1));
	while (i < j)
	{
		new[k] = str[i];
		i++;
		k++;
	}
	new[i] = 0;
	return (new);
}

int	ft_counter_word(char *str)
{
	int	i;
	int	rtrn;

	i = 0;
	rtrn = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		while (str[i] && str[i] != ' ')
		{
			if (str[i + 1] == ' ' || !str[i + 1])
				rtrn++;
			i++;
		}
	}
	return (rtrn);
}

void	ft_total(char *str, int ctrl, struct ms *tdata)
{
	int	i;
	int	start;
	int	end;
	int	indx;

	i = 0;
	start = 0;
	end = 0;
	indx = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		start = i;
		while (str[i] && str[i] != ' ' && ((str[i] >= 'a' && str[i] <= 'z')
				|| str[i] == '|' || str[i] == '-'))
		{
			if (ctrl == 1)
			{
				start = i;
				ctrl = 0;
			}
			i++;
		}
		end = i;
		tdata->str[indx] = ft_words(str, start, end);
		indx++;
		i++;
	}
}

void	ft_double_str(char *str, struct ms *tdata)
{
	tdata->cnt = ft_counter_word(str);
	tdata->str = (char **)malloc(sizeof(char *) * tdata->cnt + 1);
	ft_total(str, 1, tdata);
}

int	main(void)
{
	struct ms tdata;
	int i;

	i = 0;
	while (1)
	{
		char *input = readline("Minishell> ");
		ft_double_str(input, &tdata);
		ft_categorize(tdata);
//		printf("  %s  %s  %s  %s  \n",tdata.str[0], tdata.str[1],tdata.str[2],tdata.str[3]);
		while (i < ft_counter_word(input))
		{
			free(tdata.str[i]);
			i++;
		}
		free(input);
	}
}