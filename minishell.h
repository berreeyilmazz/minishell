/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:57:37 by havyilma          #+#    #+#             */
/*   Updated: 2023/08/25 14:02:42 by havyilma         ###   ########.fr       */
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
# include <fcntl.h>
# include <signal.h>

enum				e_types
{
	COMMAND = 1,
	FILENAME,
	PIPE,
	RED_O,
	DB_O,
	RED_I,
	DB_I,
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
	char				**str;
	int					fd_input;
	int					fd_output;
	pid_t				pid;
	struct s_executable	*next;
}				t_executable;

typedef struct s_export
{
	char			*line;
	struct s_export	*next;
}				t_export;

typedef struct s_env
{
	char			*line;
	struct s_env	*next;	
}				t_env;

struct				s_global
{
	int				pipe_cnt;
	char			**envp;
	int				exit_status;
	int				signal_status;
	int				heredoc_pid;
	int				stdout_control;
	char			*input;
	struct s_token	*tokens;
	t_executable	*exec;
	t_export		*exp;
	t_env			*env;
}					g_global;

int		ft_execve(t_executable *exec);
char	*ft_find_in_env(char *str);
void	ft_free_double_pointer(char **str);
int		ft_filename_redirection_executable(void);
int		ft_execute_starter(void);
void	ft_setting_t_executable(void);
void	ft_zero_struct_executable(t_executable	*exec);
void	ft_free_global(void);
int		ft_heredoc(char *str_endline, int fd_input);
void	ft_sig_chield(int sig);
void	eof_control_heredoc(char *line);
void	ft_close_fd(void);
void	ft_words(int i, int j, t_token **token);
void	ft_free(void);
void	ft_init(void);
int		ft_get_tokens(int i, int start);
void	ft_get_next(t_token **tmp);
int		ft_get_word(int start, int end, t_token **token);
void	get_line(void);
void	get_env(char **envp);
int		ft_get_tokens_plus(int start, int i, t_token **token);
int		ft_get_pipe_red(t_token **token, int i, int c);
int		red_pipe_or_quote(int i);
int		ft_get_type(void);
int		ft_strcmp(char *s1, char *s2);
int		ft_len(int start, int i, char quote, int cnt);
int		ft_get_word_for_quote(int start, int i, t_token **token);
int		ft_check_if_next(int i, t_token **token);
int		ft_print_cnf(void);
char	*ft_strjoin_vol2(char const *s1, char const *s2);
int		ft_exit(t_executable *exec);
void	ft_echo(t_executable *exec, int i);
void	ft_pwd(void);
int		ft_cd(t_executable *exec);
int		ft_syntax_error(void);
int		if_dollar_counter(int i, int end, int len);
int		if_dollar_handler(t_token **token, int i, int end, int k);
void	ft_env(void);
char	*get_from_env(char *word);
void	ft_export(void);
int		ft_export_plus(t_executable *exec);
void	fill_env_exp(void);
void	ft_env(void);
void	ft_export(void);
void	add_back_env(char *str);
void	add_back_exp(char *str, char flag);
char	*put_quotes(char *str);
void	take_line(t_export **tmp, int i);
char	is_there_equal_sign(char *str);
int		ft_export_plus(t_executable *exec);
void	re_fill_exp(char *str);
void	re_fill_env(char *str);
int		ft_strcmp_for_re(char *s1, char *s2);
void	ft_unset(t_executable *exec);
int		dollar_counter_for_quote(int *ij, int end, int len);
int		dollar_handler_for_quote(t_token **token, int i, int end, int*k);
int		unexpected_token(void);
char	*is_it_alnum(int *start_dollar);
void	eof_control_main(char *line);
void	signal_handler(void);
int		ft_get_while(int start, int i, t_token **token, char quote);
int		is_it_quote(int i);
void	ft_get_while_plus(t_token **token, int *star, int *k, char quote);
int		ft_i(int start);
int		ft_len(int start, int i, char quote, int cnt);
int		ft_len_plus(int *cn, char *quot, int start);
int		after_red_pipe(t_token **token);
void	change_oldpwd(char *old_loc, char *new_loc);
void	change_oldpwd_env(char *old_loc, char *new_loc);
int		ft_check_content(t_token **token, char *str);
int		check_minus(char *str);
void	ft_error_no_file(char *str);
void	ft_wait_pid(void);

#endif
