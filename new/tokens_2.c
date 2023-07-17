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

int   ft_get_quote(int i, int start, t_token **tmp)
{
    int k;
    int j;

    j = 0;
    k = 0;
    i++;
    while(g_global.input[i - k] && g_global.input[i - k] != ' ' && g_global.input[i - k] != '|')
        k++;
    start = i - k + 1;
    while (g_global.input[i] != 39)
        i++;
    i++;
    while(g_global.input[i] != ' ' && g_global.input[i] != '|')
        i++;
    ft_words(g_global.input, start, i, tmp);
    ft_get_next(tmp);
    if(g_global.input[i] == '|')
    {
        ft_get_pipe_red(tmp);
        ft_get_next(tmp);
    }
    return (i + 1);
}

int    ft_get_double_quote(int i, int start, t_token **tmp)
{
    int k;
    int j;

    j = 0;
    k = 0;
    i++;
    while(g_global.input[i - k] && g_global.input[i - k] != ' ' && g_global.input[i - k] != '|')
        k++;
    start = i - k + 1;
    while (g_global.input[i] != 34)
        i++;
    i++;
    while(g_global.input[i] != ' ' && g_global.input[i] != '|')
        i++;
    ft_words(g_global.input, start, i, tmp);
    ft_get_next(tmp);
    if(g_global.input[i] == '|')
    {
        ft_get_pipe_red(tmp);
        ft_get_next(tmp);
    }
    return (i + 1);
}

int ft_get_tokens_plus(int start, int i, t_token **token)
{
    if(start + 1 != i)
        ft_get_word(g_global.input, start, i, token);
    ft_get_pipe_red(token);
    return (i + 1);
}

int    ft_get_tokens(int i, int start)
{
    t_token *token;

    token = g_global.tokens;
    while (g_global.input[++i])
    {    
        while (g_global.input[i] && g_global.input[i] == ' ')
            i++;
        start = i;
        if(g_global.input[i] && g_global.input[i] == '|' && g_global.input[i] != 34 && g_global.input[i] != 39)
            ft_get_pipe_red(&token);
        while(g_global.input[i] && g_global.input[i] != ' ' && g_global.input[i] != '|' && g_global.input[i] != 34 && g_global.input[i] != 39)
        {
            i++;
            if ((g_global.input[i] == '|' || g_global.input[i] == '>') && g_global.input[i] != 34 && g_global.input[i] != 39)
            {
                start = ft_get_tokens_plus(start, i, &token) + 1;
                i++;
            } 
        }
        if (g_global.input[i] != '|' && g_global.input[i] != 34 && g_global.input[i] != 39)
            ft_get_word(g_global.input, start, i, &token);
        if (g_global.input[i] == 39)
            i = ft_get_quote(i, start, &token);
        else if(g_global.input[i] == 34)
            i = ft_get_double_quote(i, start, &token);
    }
    token->next = NULL;
    return (i + 1);
}

// redirectionlar ve diğer word dışındaki her şey için ayrı fonksyion yazıp if'in içine koyc







