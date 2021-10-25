/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurz <akurz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 19:25:46 by wollio            #+#    #+#             */
/*   Updated: 2021/10/25 15:31:03 by akurz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_readinput(char *line, char **envp, t_env_list **env_head)
{
	int	i;
	char **onlyForNow;

	i = 0;
	while (line[i])
	{
		if (ft_strncmp(&line[i], "echo", 4) == 0)
		{
			ft_echo(line);
			return ;
		}
		else if (ft_strncmp(line, "export", 6) == 0)
		{
			onlyForNow = ft_split(line, ' ');
			ft_export_node(env_head, onlyForNow[1]);
			return ;
		}
		else if (ft_strncmp(line, "unset", 5) == 0)
		{
			onlyForNow = ft_split(line, ' ');
			ft_delete_node(env_head, onlyForNow[1]);
			return ;
		}
		else if (ft_strncmp(&line[i], "env", 3) == 0)
		{
			// ft_env(envp);
			ft_print_list(*env_head);
			return ;
		}
		else if (ft_strncmp(&line[i], "exit", 4) == 0)
			ft_exit();
		// else if (ft_strncmp(line, "cd", 2))
		// 	ft_cd(line);
		// else if (ft_strncmp(line, "pwd", 3))
		// 	ft_pwd(line);
		// else if (ft_sys_func_chck(line))
		// 	ft_sys_func_ex(line);
		i++;
	}
	(void)envp;
	ft_error(line);
	return ;
}

int main(int argc, char **argv, char **envp)
{
	char 		*line;
	t_env_list	*env_head;
	clear();

	(void)argc;
	(void)argv;

	ft_get_env_list(envp, &env_head);
	while (1)
	{
		line = readline(ft_strjoin(getenv("USER"), "\x1b[35m @minishell \x1b[0m>> "));
		// ft_parse_input(envp, line);
		if (line != NULL)
			add_history(line);
		ft_readinput(line, envp, &env_head);
	}
	return (0);
}
