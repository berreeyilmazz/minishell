/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:57:37 by havyilma          #+#    #+#             */
/*   Updated: 2023/08/02 09:23:58 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "./libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <fcntl.h>

enum				e_types
{
	COMMAND = 1,
	FILENAME,
	PIPE,
	RED_O,
	DB_O,
	RED_I,
	DB_I,
	DOLLAR,
	INPUT,
	OUTPUT,
};

typedef struct s_token
{
	char			*content;
	enum e_types	type;
	struct s_token	*next;
}					t_token;

typedef struct s_executable
{
	char			**str;
	int				fd_input;
	int				fd_output;
	pid_t			pid;
	struct s_executable	*next;
}				t_executable;

struct				s_global
{
	int				pipe_cnt;
	char			**env;
	int				*exit_status;
	char			*input;
	struct s_token	*tokens;
	t_executable	*exec;
}					g_global;

//Mert

int		ft_execve(t_executable *exec);
char	*ft_find_in_env(char *str);
void	ft_free_double_pointer(char **str);
int		ft_filename_redirection_executable(void);
int		ft_execute_starter(void);
int		ft_setting_t_executable(void);
void	ft_zero_struct_executable(t_executable	*exec);

//berre

void				ft_words(int i, int j, t_token **token);
void				ft_free(void);
void				ft_init(void);
void				write_global(void);
int					ft_get_tokens(int i, int start);
void				ft_get_next(t_token **tmp);
int					ft_get_word(int start, int end, t_token **token);
void				get_line(void);
void				get_env(char **envp);
int					ft_get_tokens_plus(int start, int i, t_token **token);
int					ft_get_pipe_red(t_token **token, int i);
int					red_pipe_or_quote(int i);
int					ft_get_type(void);
int					ft_strcmp(char *s1, char *s2);
void				ft_types(t_token **token);
int					ft_len(int start, int i, char quote, int cnt);
int					ft_get_word_for_quote(int start, int i, t_token **token);
int					ft_check_if_next(int i, t_token **token);
int					ft_print_cnf(void);
char				*ft_strjoin_vol2(char const *s1, char const *s2);
int					ft_exit(t_executable *exec);
void 				ft_echo(t_executable *exec);
void				ft_pwd();
void				ft_cd(t_executable *exec);
int					ft_syntax_error(void);
int					if_dollar_counter(int i, int end, int len);
int 				turning_into_env(int   *m, t_token **token, int *index);
int					if_dollar_handler(t_token **token, int i, int end, int k);
void    ft_env();



#endif

/*

bash-3.2$ echo berre'
> 
bash-3.2$ "ech'o" berre
bash: ech'o: command not found
bash-3.2$ echo "berre
> "
berre

bash-3.2$ echo "mer
> t koroglu"
mer
t koroglu

*/



/*
MERT yapılacak
-Yapılacaklar listesi

MERT soru
"ls |" ne yapmalıyız?



BERRE;

*echo \"berre\"  ----zorunlu değilmiş
*ENTER | newline
*echo
*exit

*cd
*export
*unset
*/