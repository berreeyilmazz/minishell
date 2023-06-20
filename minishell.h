/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:57:37 by havyilma          #+#    #+#             */
/*   Updated: 2023/06/20 19:25:27 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

#define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct ms
{
	char	*command;
	char	*argument;
	int		arg_c;
	char	flg;
	char	**str;
};


struct ms tdata;
int	ft_alphalen(char *input);
int	ft_len_u_space(char *input);
int	ft_print_cnf();
int	ft_parser(char *input, struct ms *tdata);



#endif


//çalışanlar  "l"s""

//çalışmasın 'l"s"'