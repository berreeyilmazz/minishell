#include "minishell.h"

char    *ft_words(char *str, int i, int j)
{
    char *new;
    int k;

    k = 0;
    new = malloc(sizeof(char) * (j - i + 1));
    while(i < j)
    {
        new[k] = str[i];
        i++;
        k++;
    }
    new[i] = 0;
    return (new);
}

int ft_counter_word(char *str)
{
    int i;
    int rtrn;

    i = 0;
    rtrn = 0;
    while(str[i])
    {
        while(str[i] && str[i] == ' ')
            i++;
        while(str[i] && str[i] != ' ')
        {
            if(str[i + 1] == ' ' || !str[i + 1])
                rtrn++;
            i++;
        }
    }
    return (rtrn);
}

void ft_total(char *str, int ctrl, struct ms *tdata)
{
    int     i;
    int     start;
    int     end;
    int     indx;

    i = 0;
    start = 0;
    end = 0;
    indx = 0;
    while (str[i])
    {    
        while(str[i] && str[i] == ' ')
            i++;
        start = i;
        while (str[i] && str[i] != ' ' && ((str[i] >= 'a' && str[i] <= 'z') || str[i] == '|' || str[i] == '-'))
        {
            if (ctrl == 1)
            {
                start = i;
                ctrl = 0;
            }
            i++;
        }
        end = i;
        tdata->str[indx] = ft_words(str, start, end);
        indx++;
        i++;
    }
}

void ft_double_str(char *str, struct ms *tdata)
{
    int count;

    count = ft_counter_word(str);
    tdata->str = (char **)malloc(sizeof(char *) * count + 1);
    ft_total(str, 1, tdata);
}

int main()
{
	struct ms tdata;
    int i;

    i = 0;
    while (1)
    {
        char *input = readline("Minishell> ");
        ft_double_str(input, &tdata);
        while (i < ft_counter_word(input))
        {
            printf("   i %d  : %s\n", i, tdata.str[i]);
            i++;
        }
    
    }   
}