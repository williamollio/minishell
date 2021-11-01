/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurz <akurz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:47:44 by wollio            #+#    #+#             */
/*   Updated: 2021/11/01 17:33:28 by akurz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(char *line)
{
	char	*print;

	print = ft_substr(line, 5, ft_strlen(line) - 5);
	printf("%s\n", print);
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


