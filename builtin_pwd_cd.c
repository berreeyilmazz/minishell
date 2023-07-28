/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 03:43:11 by havyilma          #+#    #+#             */
/*   Updated: 2023/07/28 08:41:15 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

havyilma@k1m39s05 minishell_vol2 % cc -dM -E -xc - <<< '#include <sys/syslimits.h>' | grep -i ' [NP]A.._MAX'
#define NAME_MAX 255
#define PATH_MAX 1024

*/

void    ft_pwd()
{
	char *path;

	path = malloc(sizeof(char) * 1024);
	if(getcwd(path, sizeof(path)) != NULL)
		printf("%s\n", path);
	else	
		printf("pwd: cannot access: No such file or directory\n");
	free(path);
	system("leaks minishell"); 
	
}

void	ft_cd(t_executable *exec)
{
	char	path_now[1024];
	char	*new;
	char	*new2;

	if(!exec->str[1])
		return;
	if (!ft_strncmp(exec->str[1], "~", 1) || !exec->str[1])
	{
		chdir("/Users/havyilma");  // $USER
		system("leaks minishell");
		return;
	}
	getcwd(path_now, sizeof(path_now));
	new = ft_strjoin(path_now, "/");
	new2 = ft_strjoin(new, exec->str[1]);
	chdir(new2);
	free(new);
	free(new2);
	system("leaks minishell"); 

}