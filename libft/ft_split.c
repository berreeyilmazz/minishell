/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 19:43:12 by mkoroglu          #+#    #+#             */
/*   Updated: 2022/11/14 16:51:11 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	counter_word(const char *str, char c)
{
	int	i;
	int	count_word;

	i = 0;
	count_word = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			count_word++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count_word);
}

static char	*ft_word_add(const char *str, char c)
{
	int		count_letter;
	int		i;
	char	*array_in_word;

	i = 0;
	count_letter = 0;
	while (str[count_letter] && str[count_letter] != c)
		count_letter++;
	array_in_word = (char *)malloc(sizeof(char) * (count_letter + 1));
	if (!array_in_word)
		return (0);
	while (str[i] && str[i] != c)
	{
		array_in_word[i] = str[i];
		i++;
	}
	array_in_word[i] = '\0';
	return (array_in_word);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		i_word;
	int		count_word;
	char	**word_array;

	i = 0;
	i_word = 0;
	if (!s)
		return (0);
	count_word = counter_word(s, c);
	word_array = (char **)malloc((sizeof(char *)) * (count_word + 1));
	if (!word_array)
		return (0);
	while (s[i] && (i_word != count_word))
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			word_array[i_word++] = ft_word_add(s + i, c);
		while (s[i] && s[i] != c)
			i++;
	}
	word_array[count_word] = 0;
	return (word_array);
}
