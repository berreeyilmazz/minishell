/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:57:37 by havyilma          #+#    #+#             */
/*   Updated: 2023/07/05 17:09:14 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

enum
{
	WORD,
	PIPE,
	R_OUT,
	R_IN,
	R_CREAT,

};

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

struct		ms
{
	char	*command;
	char	*argument;
	int		arg_c;
	char	*flg;
	char	**str;
	int		cnt;
};

struct ms	tdata;
int			ft_alphalen(char *input);
int			ft_len_u_space(char *input);
int			ft_print_cnf(void);
int			ft_parser(char *input, struct ms *tdata);

char		*ft_words(char *str, int i, int j);
int			ft_counter_word(char *str);
void		ft_total(char *str, int ctrl, struct ms *tdata);
void		ft_double_str(char *str, struct ms *tdata);

#endif // echo " selam eren naber ? nasıl gidiyor ?v  " > a | cat a | tr i o

// 4  word " pipe word word pipe word word word
//1 5
//
//ls –al | sort >& out

//çalışanlar  "l"s""

//çalışmasın 'l"s"'