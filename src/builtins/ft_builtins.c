/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurz <akurz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:47:44 by wollio            #+#    #+#             */
/*   Updated: 2021/11/02 16:58:09 by akurz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(char *str, char *arg)
{
	char	*join_space;
	char	*join_str;
	
	if (ft_strncmp(arg, "-n", 2) == 0 && ft_strlen(arg) == 2)
		printf("%s", str);
	else if (arg[0] == '\0')
		printf("%s\n", str);
	else
	{
		join_space = ft_strjoin(arg, " ");
		join_str = ft_strjoin(join_space, str);
		free(join_space);
		printf("%s\n", join_str);
		free(join_str);
	}
}

void	ft_exit(void)
{
	exit(0);
}

// void	ft_env(char **envp)
// {
// 	int		pipes[2];
// 	pid_t	childpid;
// 	char	**cmd;

// 	cmd = malloc(sizeof(char *) * 2);
// 	cmd[0] = "env";
// 	cmd[1] = NULL;
// 	if (pipe(pipes) == -1)
// 	{
// 		perror("pipe");
// 		exit(0);
// 	}
// 	childpid = fork();
// 	if (childpid == -1)
// 	{
// 		perror("fork");
// 		exit(0);
// 	}
// 	if (childpid == 0)
// 		execve("/usr/bin/env", cmd, envp);
// 	else
// 	{
// 		wait(NULL);
// 		return ;
// 	}
// }


