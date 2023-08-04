/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 09:06:34 by havyilma          #+#    #+#             */
/*   Updated: 2023/08/04 12:26:34 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    fill_env_exp()
{
    int i;
    t_export *exp;
    t_env    *env;
    
    g_global.exp = malloc(sizeof(t_export));
    g_global.env = malloc(sizeof(t_env));
    exp = g_global.exp;
    env = g_global.env;
    i = -1;    
    while(g_global.envp[++i] != NULL)
    {
        take_line(&exp, i);
        if(!g_global.envp[i + 1])
            break;
        exp->next = malloc(sizeof(t_export));
        exp = exp->next;
    }
    exp->next = NULL;
    i = -1;
    while(g_global.envp[++i] != NULL)
    {
        env->line = ft_strdup(g_global.envp[i]);
        if(!g_global.envp[i + 1])
            break;
        env->next = malloc(sizeof(t_env));
        env = env->next;
    }
    env->next = NULL;
}


void    ft_env()
{
    t_env   *env;

    env = g_global.env;
    while(env)
    {
        printf("%s\n", env->line);
        if(env->next == NULL)
            return;
        env = env->next;
    }
}

void    ft_export()
{
    t_export    *tmp;

    tmp = g_global.exp;
    while (tmp)
    {
        printf("%s\n",tmp->line);
        if (tmp->next == NULL)
            return;
        tmp = tmp->next;
    }
}

void    add_back_env(char *str)
{
    t_env    *env;

    env = g_global.env;
    while(env->next)
        env = env->next;
    env->next = malloc(sizeof(t_env));
    env = env->next;
    env->line = ft_strdup(str);
    env->next = NULL;
}

void    add_back_exp(char *str, char flag)
{
    t_export    *exp;
    char        *line;

    exp = g_global.exp;
    while(exp->next)
        exp = exp->next;
    exp->next = malloc(sizeof(t_export));
    exp = exp->next;
    if (flag == '=')
        line = put_quotes(str);
    else
        line = ft_strdup(str);
    exp->line = ft_strjoin("declare -x ", line);
    free(line);
    exp->next = NULL;
}

char    *put_quotes(char *str)
{
    char    *new;
    int     n;
    int     s;

    n = 0;
    s = 0;
    new = malloc(sizeof(char) * (ft_strlen(str) + 3));
    while(str[s])
    {
        new[n] = str[s];
        if(str[s] == '=')
        {
            n++;
            new[n] = 34;
        }
        s++;
        n++;
    }
    new[n++] = 34;
    new[n] = '\0';
    return (new);
}

void    take_line(t_export **tmp, int i)
{
    char        *hey;
    
    hey = put_quotes(g_global.envp[i]);
    (*tmp)->line = ft_strjoin("declare -x ", hey);
    free(hey);  
}

void    take_str(t_export **tmp, char *str)
{
    char    *line;
    
    free((*tmp)->line);
    if( is_there_equal_sign(str) == '=')
    {
        line = put_quotes(str);
        (*tmp)->line = ft_strjoin("declare -x ", line);
        free(line);
    }
    else
        (*tmp)->line = ft_strjoin("declare -x ", str);   
}    

char    is_there_equal_sign(char *str)
{
    int i;
    char flag;
    
    i = 0;
    flag = '\0';
    while(str[i])
    {
        if(str[i] == '=')
            flag = '=';
        i++;
    }
    i = 0;
    return(flag);
}


int    ft_export_plus(t_executable *exec)
{
    int         k;
    int         i;

    i = 1;
    while (exec->str[i])
    {
        if(exec->str[i][0] >= 48 && exec->str[i][0] <= 57)
        {
            printf("export: '%s': not a valid identifier\n", exec->str[i]);
            i++;
            continue;
        }
        k = 0;
        re_fill_exp(exec->str[i]);
        if(is_there_equal_sign(exec->str[i]) == '=')
            re_fill_env(exec->str[i]);
        i++;
    }
    return(0);
}

int    re_fill_exp(char *str)
{
    t_export    *old_exp;
    int         i;
    int         d;
    
    old_exp = g_global.exp;
    while(old_exp)
    {
        i = 0;
        d = 11;
        while(old_exp->line[d] == str[i] && old_exp->line[d] != '=')
        {
            i++;
            d++;      
        }
        if((!old_exp->line[d] || !str[i]) || (old_exp->line[d] == str[i]))
        {
            if(old_exp->line[d] && !str[i])
                return(0);
            take_str(&old_exp, str);
            return (0);
        }
        old_exp = old_exp->next;
    }
    add_back_exp(str, is_there_equal_sign(str));
    return(0);
}


int re_fill_env(char *str)
{
    t_env       *old_env;
    int         i;
    int         d;

    old_env = g_global.env;
    while(old_env)
    {
        i = 0;
        d = 0;
        while(old_env->line[d] == str[i] && old_env->line[d] != '=')
        {
            i++;
            d++;      
        }
        if((old_env->line[d] == str[i]) || (!old_env->line[d] || !str[i]))
        {
            free(old_env->line);
            old_env->line = ft_strdup(str);
            return (0);
        }
        old_env = old_env->next;
    }
    add_back_env(str);        
    return (0); 
}