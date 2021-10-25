/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurz <akurz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:47:44 by wollio            #+#    #+#             */
/*   Updated: 2021/10/25 15:50:32 by akurz            ###   ########.fr       */
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

void	ft_delete_node(t_env_list **env_head, char *str)
{
	t_env_list	*temp;
	t_env_list	*prev;
	
	temp = *env_head;
	if (ft_strncmp((*env_head)->var, str, ft_strlen((*env_head)->var)) == 0)
	{
		(*env_head) = (*env_head)->next;
		free(temp);
	}
	else
	{
		while (ft_strncmp(temp->next->var, str, ft_strlen(temp->next->var)) != 0)
			temp = temp->next;
		prev = temp;
		temp = temp->next;
		prev->next = temp->next;
		free(temp);
	}
}

void	ft_export_node(t_env_list **env_head, char *str)
{
	t_env_list	*temp;
	t_env_list	*temp_2;
	t_env_list	*newNode;

	temp = *env_head;
	while (ft_strncmp(temp->next->var, "_", ft_strlen(temp->next->var)))
	{
		temp = temp->next;
	}
	temp_2 = temp->next;
	newNode = malloc(sizeof(t_env_list));
	newNode->full = str;
	newNode->var = ft_get_var(str);
	newNode->content = ft_get_content(str);
	temp->next = newNode;
	newNode->next = temp_2;
	if (*env_head == NULL)
	{
		*env_head = newNode;
		return ;
	}
	return ;
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

// void ft_cd(char *line)
// {
// 	(void)line;
// 	printf("cd command");
// }

// void ft_pwd(char *line)
// {
// 	(void)line;
// 	printf("pwd command");
// }

// void ft_export(char *line)
// {
// 	(void)line;
// 	printf("export command");
// }

// void ft_unset(char *line)
// {
// 	(void)line;
// 	printf("unset command");
// }

// void ft_env(char *line)
// {
// 	(void)line;
// 	printf("env command");
// }
