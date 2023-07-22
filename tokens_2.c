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

int ft_len(int start, int i)
{
    char    quote;
    int     cnt;
    (void)i;

    cnt = 0;
    quote = '\0';
    while(g_global.input[start])
    {
        if (g_global.input[start] == 34 || g_global.input[start] == 39)
        {
            if (quote == '\0')
                quote = g_global.input[start];
            else
            {
                if(g_global.input[start] == quote)
                    quote = '\0';
                else
                    cnt++;
            }
            start++;
        }
        while(g_global.input[start] && g_global.input[start] != 34 && g_global.input[start] != 39)        {
            cnt++;
            start++;
        }
        if (g_global.input[start] == 34 || g_global.input[start] == 39)
        {
            if (quote == '\0')
                quote = g_global.input[start];
            else
            {
                if(g_global.input[start] == quote)
                    quote = '\0';
                else
                    cnt++;
            }
            start++;
        }
        while(g_global.input[start] && g_global.input[start] != 34 && g_global.input[start] != 39)        {
            cnt++;
            start++;
        }
        if (g_global.input[start] == 34 || g_global.input[start] == 39)
        {
            if (quote == '\0')
                quote = g_global.input[start];
            else
            {
                if(g_global.input[start] == quote)
                    quote = '\0';
                else
                    cnt++;
            }
            start++;
        }
    }
    return (cnt);
}


int    ft_get_word_for_quote(int start, int i, t_token **token)
{
    char    quote;
    int     j;
    int     k;

    k = 0;
    j = 0;
    quote = '\0';
    while(g_global.input[i - j] && red_pipe_or_quote(i - j) != ' ' && red_pipe_or_quote(i - j) != 1)
        j++;
    start = i;
    if (j != 0)
        start = i - j + 1;
    i++;
    while (g_global.input[i] && g_global.input[i] != 34)
        i++;
    i++;
    while (g_global.input[i] && red_pipe_or_quote(i) != 32)
        i++;
    (*token)->content = malloc(sizeof(char)* (i - start + 1));
    while(g_global.input[start])
    {
        if (g_global.input[start] == 34 || g_global.input[start] == 39)
        {
            if (quote == '\0')
                quote = g_global.input[start];
            else
            {
                if(g_global.input[start] == quote)
                    quote = '\0';
                else
                    (*token)->content[k++] = g_global.input[start];
            }
            start++;
        }

        while(g_global.input[start] && g_global.input[start] != 34 && g_global.input[start] != 39)
            (*token)->content[k++] = g_global.input[start++];
        if (g_global.input[start] == 34 || g_global.input[start] == 39)
        {
            if (quote == '\0')
                quote = g_global.input[start];
            else
            {
                if(g_global.input[start] == quote)
                    quote = '\0';
                else
                    (*token)->content[k++] = g_global.input[start];
            }
            start++;
        }
        while(g_global.input[start] && g_global.input[start] != 34 && g_global.input[start] != 39)
            (*token)->content[k++] = g_global.input[start++];
        if (g_global.input[start] == 34 || g_global.input[start] == 39)
        {
            if (quote == '\0')
                quote = g_global.input[start];
            else
            {
                if(g_global.input[start] == quote)
                    quote = '\0';
                else
                    (*token)->content[k++] = g_global.input[start];
            }
            start++;
        }
    }
    (*token)->content[k] = '\0';
    return (i);
}

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
        printf("start:%d, end:%d\n", start, i);
        if (red_pipe_or_quote(i) == 1)
            i = ft_get_tokens_plus(start, i, &token);
        else if(g_global.input[i] == 34)
            i = ft_get_word_for_quote(start, i, &token) + 1;
        else if (g_global.input[i] == 39)
            i = ft_get_word_for_quote(start, i, &token) + 1;
        else if (red_pipe_or_quote(i) == 32)
            i = ft_get_word(g_global.input, start, i, &token);
        else if(!g_global.input[i] && red_pipe_or_quote(start) == 32)
            i = ft_get_word(g_global.input, start - 1, i, &token);
        else if(!g_global.input[i])
            i = ft_get_word(g_global.input, start, i, &token);
    }
    token = NULL;
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

