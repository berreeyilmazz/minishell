#include "minishell.h"

int	ft_counter_word(char *str)
{
	int	i;
	int	rtrn;

	i = 0;
	rtrn = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		while (str[i])
		{
			if (ft_check_quote_detailed(i))
				rtrn += 2;
			else if (ft_check_quotes_2(i))
				rtrn += 1;
			else if (ft_check_quotes_4(i))
				rtrn += 1;
			else if(ft_check_quotes_0(i))
				rtrn += 2;
			else if(ft_check_quotes(i)) 
				rtrn += 2;
			else if((str[i] != 32 && (str[i + 1] == 32 || !str[i + 1])))
				rtrn+=1;
			i++;
		}
	}
	g_global.cnt = rtrn;
	printf("cnt:  %d\n",g_global.cnt);
	return (rtrn);
}
// "|" eksik kALDI

int	ft_check_quote_detailed(int	i)
{
	if(red_pipe_or_quote(i) == 1 && (red_pipe_or_quote(i - 1) != 32) && red_pipe_or_quote(i + 1) != 34 && red_pipe_or_quote(i - 1) != 34)
		return (1);
	return (0);
	
}

int	ft_check_quotes_4(int i)
{
	if (red_pipe_or_quote(i) == 1 && ((red_pipe_or_quote(i - 1) == ' ' 
	&& red_pipe_or_quote(i + 1) != 32) 
	|| (red_pipe_or_quote(i + 1) == ' ' && red_pipe_or_quote(i - 1) != 32)))
		return (1);
	return (0);
}

int	ft_check_quotes_0(int i)
{
	if (red_pipe_or_quote(i) == 1 && ((red_pipe_or_quote( i - 1) != 34 && 
		red_pipe_or_quote(i + 1) == 34) || (red_pipe_or_quote( i + 1) != 34 
		&& red_pipe_or_quote(i - 1) == 34)))
		return (1);
	return (0);
}

int	ft_check_quotes(int i)
{
	if(red_pipe_or_quote(i) == 1 && red_pipe_or_quote(i - 1) != ' ' 
		&& red_pipe_or_quote(i + 1) != ' '
		&& red_pipe_or_quote(i + 1) != 34 
		&& red_pipe_or_quote(i - 1) != 34)
		return(1);
	if(red_pipe_or_quote(i) == 1 && red_pipe_or_quote(i - 1) != ' ' 
		&& red_pipe_or_quote(i + 1) != ' '
		&& red_pipe_or_quote(i + 1) != 39 
		&& red_pipe_or_quote(i - 1) != 39)
		return (1);
	return (0);
}

int	ft_check_quotes_2(int i)
{
	if(red_pipe_or_quote(i) == 1 && ((red_pipe_or_quote(i - 1) != ' ' || red_pipe_or_quote(i + 1) == ' ') 
		|| (red_pipe_or_quote(i + 1) != ' ' || red_pipe_or_quote(i - 1) == ' ')) 
			&& red_pipe_or_quote(i + 1) != 34 && red_pipe_or_quote(i - 1) != 34)
		return (1);
	if(red_pipe_or_quote(i) == 1 && ((red_pipe_or_quote(i - 1) != ' ' || red_pipe_or_quote(i + 1) == ' ') 
		|| (red_pipe_or_quote(i + 1) != ' ' || red_pipe_or_quote(i - 1) == ' ')) 
			&& red_pipe_or_quote(i + 1) != 39 && red_pipe_or_quote(i - 1) != 39)
			return(1);
	return (0);
}


void	ft_words(char *str, int i, int j, t_token **token)
{
	int		k;

	k = 0;
	(*token)->content = malloc(sizeof(char) * (j - i + 1));
	while (i < j)
	{
		(*token)->content[k] = str[i];
		i++;
		k++;
	}
	(*token)->content[k] = '\0';
}

void    ft_get_next(t_token **tmp)
{
    if(g_global.cnt > 1)
    {
       (*tmp)->next = malloc(sizeof(t_token));
       (*tmp) = (*tmp)->next;
       g_global.cnt--;
    }
}

int    ft_get_pipe_red(t_token **token, int i)
{
	if(g_global.input[i] == '|')
		(*token)->content = ft_strdup("|");
	else if(g_global.input[i] == '>' && g_global.input[i + 1] == '>')
	{
		(*token)->content = ft_strdup(">>");
		i += 1;
	}
	else if(g_global.input[i] == '<' && g_global.input[i + 1] == '<')
	{
		(*token)->content = ft_strdup("<<");
		i += 1;
	}
	else if(g_global.input[i] == '>')
		(*token)->content = ft_strdup(">");
	else if(g_global.input[i] == '<')
		(*token)->content = ft_strdup("<");
	ft_get_next(token);
	g_global.pipe_cnt++;
	return (i + 1);

}

int    ft_get_word(char *str, int start, int end, t_token **token)
{
	ft_words(str, start, end, token);
	ft_get_next(token);
	return (end);
}


