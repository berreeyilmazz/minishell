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
    
    k = 0;
    while(g_global.input[i - k] && red_pipe_or_quote(i - k) != ' ')
        k++;
    start = i;
    if (k != 0)
        start = i - k + 1;
    i++;
    while (g_global.input[i] && g_global.input[i] != 39)
        i++;
    i++;
    while (g_global.input[i] && red_pipe_or_quote(i) != 32)
        i++;
    ft_words(g_global.input, start, i, tmp);
    ft_get_next(tmp);
    if(red_pipe_or_quote(i) == 1)
        i = ft_get_pipe_red(tmp, i);
    return (i);
}

int    ft_get_double_quote(int i, int start, t_token **tmp)
{
    int k;

    k = 0;
    while(g_global.input[i - k] && red_pipe_or_quote(i - k) != ' ')
        k++;
    start = i;
    if (k != 0)
        start = i - k + 1;
    i++;
    while (g_global.input[i] && g_global.input[i] != 34)
        i++;
    i++;
    while (g_global.input[i] && red_pipe_or_quote(i) != 32)
        i++;
    ft_words(g_global.input, start, i, tmp);
    ft_get_next(tmp);
    if (red_pipe_or_quote(i) == 1)
        return (i);
    return (i);
}
/*
int ft_len(int start, int i, char ctrl)
{
    int cnt;

    cnt = 0;
    while (g_global.input[start] && g_global.input[start] != 32)
    {
        if(g_global.input[start] != ctrl)
            cnt++;
        else
            break;
    }
}

char *ft_get_word_for_quote(int start, int i, t_token **token)
{
    int cnt;
    int stay;
    char   *str;

    str = malloc(sizeof(char)* (end - start + 1)
    cnt = 0;
    stay = start;
    start++;
    while(g_global.input[start] && g_global.input[start] != 34 && g_global.input[start] != 39 && g_global.input[start] != 32)
        str[i++] = g_global.input[start++];
    while (g_global.input[start] && g_global.input[start] != 32)
    {
        if(g_global.input[start] != 34)
            str[i] = g_global.input[start++];
        else
            break;
    }
    while (g_global.input[start] && g_global.input[start] != 32)
    {
        if(g_global.input[start] != 39)
            str[i] = g_global.input[start++];
        else
            break;
    }
    str[i] = '\0';
    return (str);
}
*/

int ft_get_tokens_plus(int start, int i, t_token **token)
{
    if(red_pipe_or_quote(start) != 32 && start != i)
        i = ft_get_word(g_global.input, start, i, token);
    i = ft_get_pipe_red(token, i);
    g_global.pipe_cnt++;
    return(i);
}

int    ft_get_tokens(int i, int start)
{
    t_token *token;
    token = g_global.tokens;
    while (g_global.input[i])
    {
        while (g_global.input[i] && g_global.input[i] == ' ')
            i++;
        start = i;
        while((g_global.input[i] && red_pipe_or_quote(i) == 0))
                i++;
        if (red_pipe_or_quote(i) == 1)
            i = ft_get_tokens_plus(start, i, &token);
        else if(g_global.input[i] == 34)
            i = ft_get_double_quote(i, start, &token);
        else if (g_global.input[i] == 39)
            i = ft_get_quote(i, start, &token);
        else if (red_pipe_or_quote(i) == 32)
            i = ft_get_word(g_global.input, start, i, &token);
        else if(!g_global.input[i] && red_pipe_or_quote(start) == 32)
            i = ft_get_word(g_global.input, start - 1, i, &token);
        else if(!g_global.input[i])
            i = ft_get_word(g_global.input, start, i, &token);
    }
    token->next = NULL;
    return (i);
}

int red_pipe_or_quote(int i)
{
    if (g_global.input[i] == '|' || g_global.input[i] == '>' || g_global.input[i] == '<')
        return (1);
    else if (g_global.input[i] == 34)  
        return (34);
    else if (g_global.input[i] == 39)
        return (39);
    else if(g_global.input[i] == ' ')
        return (32);
    return (0);
}

