/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 09:06:34 by havyilma          #+#    #+#             */
/*   Updated: 2023/08/02 09:43:23 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_env()
{
    char    **strs;
    int     i;
    
    i = 0;
    while(g_global.env[i])
        i++;
    strs = malloc(sizeof(char)* (i + 1));
    i = 0;
    while(g_global.env[i])
    {
        strs[i] = ft_strdup(g_global.env[i]);
        i++;
    }
    strs[i] = NULL;
    i = 0;
    while(strs[i])
    {
        printf("%s\n", strs[i]);
        i++;
    }
    i = 0;
    
}
/*
void    ft_export()
{
        char    **strs;
    int     i;
    
    i = 0;
    while(g_global.env[i])
        i++;
    strs = malloc(sizeof(char)* (i + 1));
    i = 0;
    
}

*/