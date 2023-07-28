/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 01:23:46 by havyilma          #+#    #+#             */
/*   Updated: 2023/07/28 08:21:06 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exit_pre_request(char **str)
{
    int i;

    i = 1;
    while((str[i]))
        i++;
    return (i);
}

int is_it_numeric(char *str, int one_or_more)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!(str[i] >= 48 && str[i] <= 57))
        {
            printf("exit\nexit: %c: numeric argument required\n", str[i]);
            exit (1);
        }
        i++;
    }
    if (one_or_more == 2)
    {
        printf("exit\n");
        exit (1);
    }
    else if (one_or_more > 2)
        printf("exit\nexit: too many arguments\n");
    return (0);
}

int ft_exit(t_executable *exec)
{
    int argc;
    argc = exit_pre_request(exec->str);
    if (argc == 1)
    {
        printf("exit\n");
        exit(1);
    }
    else if (argc >= 2)
        is_it_numeric(exec->str[1], argc);
    return(0);
}