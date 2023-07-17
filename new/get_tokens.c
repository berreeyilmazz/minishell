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
		while (str[i] && !(str[i] == ' '))
		{
			if(str[i] == '|' && str[i - 1] != ' ' && str[i + 1] != ' ')
				rtrn += 3;
			else if (str[i] == '|' && ((str[i - 1] != ' ' || str[i + 1] == ' ') || (str[i + 1] != ' ' || str[i - 1] == ' ')))
				rtrn += 23;
			i++;
		}
	}
	g_global.cnt = 3;
	printf("//// %d\n", g_global.cnt);
	return (rtrn);
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

void    ft_get_pipe_red(t_token **token)
{
    (*token)->content = ft_strdup("|");
    ft_get_next(token);
	g_global.pipe_cnt++;

}

void    ft_get_word(char *str, int start, int end, t_token **token)
{
/*	if (start != 0)
    	ft_words(str, start - 1, end, token);
	else*/
	if(str[start] == ' ')
		start++;
	ft_words(str, start, end, token);
	ft_get_next(token);
}


//leak ft_get_word de !!!!!