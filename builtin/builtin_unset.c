/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:13:12 by havyilma          #+#    #+#             */
/*   Updated: 2023/08/04 17:45:14 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    delete_identifier_exp(char *str)
{
    t_export    *exp;
    t_export    *new_next;
    char        *without_declare;

    exp = g_global.exp;
    without_declare = ft_substr(exp->line, 11, ft_strlen(exp->line));
    if(ft_strcmp(without_declare, str) == '=')
    {
        free(exp->line);
        g_global.exp = exp->next;
        free(exp);
        free(without_declare);
        return(0);
    }
    free(without_declare);
    while(exp->next->next)
    {   
        without_declare = ft_substr(exp->next->line, 12, ft_strlen(str));
        if(ft_strcmp(without_declare, str) == '=')
        {
            if(exp->next->next == NULL)
            {
                free(exp->next);
                free(exp->next->line);
                exp->next = NULL;
                free(without_declare);
                return(0);
            }
            new_next = exp->next->next;
            free(exp->next->line);
            free(exp->next);
            exp->next = new_next;
            free(without_declare);
            printf("denemeeeeee\n");
            return (0);
        }
        exp = exp->next;
        free(without_declare);
    }
    if (exp && !exp->next)
    {    
        without_declare = ft_substr(exp->next->line, 11, ft_strlen(str));
        if(ft_strcmp(without_declare, str) == '=')
        {    
            free(exp->line);
            free(exp);
            exp = NULL;
            exp->line = NULL;
        }
        free(without_declare);
    }
    return (0);
}

int    delete_identifier_env(char *str)
{
    t_env    *env;
    t_env    *new_next;

    env = g_global.env;
    if(ft_strcmp(env->line, str) == '=')
    {
        free(env->line);
        g_global.env = env->next;
        free(env);
    }
    while(env->next)
    {
        if(ft_strcmp(env->next->line, str) == '=')
        {
            new_next = env->next->next;
            free(env->next->line);
            free(env->next);
            env->next = new_next;
            return (1);
        }
        env = env->next;
    }
    if (env && !env->next)
    {       
        if(ft_strcmp(env->line, str) == '=')
        {
            free(env->line);
            free(env);
            env = NULL;
            env->line = NULL;
        }
    } 
    return (0);
}

void    ft_unset(t_executable *exec)
{
    int i;

    i = 1;
    while (exec->str[i])
    {
        if(exec->str[i][0] >= 48 && exec->str[i][0] <= 57)
        {
            printf("export: '%s': not a valid identifier\n", exec->str[i]);
            i++;
            continue;
        }
        printf("+++++1111\n");
        delete_identifier_exp(exec->str[i]);
        printf("+++++2222\n");
        delete_identifier_env(exec->str[i]);
        i++;
    }
    
}