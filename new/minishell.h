/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:57:37 by havyilma          #+#    #+#             */
/*   Updated: 2023/07/11 13:25:19 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H


# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

struct s_global
{
	int			pipe_cnt;
	//char		**env;
	char		*input;
	int			cnt;
	struct s_token	*tokens;
}		g_global;
/*
enum e_types
{
	WORD = 1,
	RED_I,
	RED_O,
	DB_O,
	PIPE,
	DB_I,
	DOLLAR,
	INPUT,
	OUTPUT,

};*/

typedef	struct	s_token
{
	char			*content;
//	enum e_types	type;
	struct s_token	*next;
	int				type;
}				t_token;

void 	ft_content(char *str);
void	ft_words(char *str, int i, int j, t_token **token);
int		ft_counter_word(char *str);
int		ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
void	ft_categorize(t_token *came);
void	ft_free();
void	ft_init();
void 	write_global();
int		ft_get_tokens(int i, int start);
void    ft_get_pipe_red(t_token **token);
void    ft_get_next(t_token **tmp);
void	ft_get_word(char *str, int start, int end, t_token **token);
void	get_line();
void    ft_distribute_input();
int		ft_get_quote(int i, int start, t_token **tmp);
int		ft_get_double_quote(int i, int start, t_token **tmp);
int 	ft_get_tokens_plus(int start, int i, t_token **token);
void    ft_get_pipe_red(t_token **token);
int		ft_strcmp(char *s1, char *s2);




#endif



// 

//ls –al | sort >& out

//çalışanlar  "l"s""

//çalışmasın 'l"s"'