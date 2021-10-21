/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wollio <wollio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 19:25:46 by wollio            #+#    #+#             */
/*   Updated: 2021/10/21 18:05:40 by wollio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_readinput(char *line, char **envp)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_strncmp(&line[i], "echo", 4) == 0)
		{
			ft_echo(line);
			return ;
		}
		// else if (ft_strncmp(line, "cd", 2))
		// 	ft_cd(line);
		// else if (ft_strncmp(line, "pwd", 3))
		// 	ft_pwd(line);
		// else if (ft_strncmp(line, "export", 6))
		// 	ft_export(line);
		// else if (ft_strncmp(line, "unset", 5))
		// 	ft_unset(line);
		if (ft_strncmp(&line[i], "env", 3) == 0)
		{
			ft_env(envp);
			return ;
		}
		if (ft_strncmp(&line[i], "exit", 4) == 0)
			ft_exit();
		// else if (ft_sys_func_chck(line))
		// 	ft_sys_func_ex(line);
		i++;
	}
	ft_error(line);
	return ;
}

int main(int argc, char **argv, char **envp)
{
	char *line;
	clear();

	(void)argc;
	(void)argv;

	while (1)
	{
		line = readline(ft_strjoin(getenv("USER"), "\x1b[35m @minishell \x1b[0m>> "));
		if (line != NULL)
			add_history(line);
		ft_readinput(line, envp);
	}
	(void)argc;
	(void)argv;
	return (0);
}
