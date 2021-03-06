/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wollio <wollio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:42:01 by wollio            #+#    #+#             */
/*   Updated: 2021/11/18 18:50:57 by wollio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_list(t_env *head)
{
	while (head != NULL)
	{
		ft_putendl_fd(head->full, 1);
		head = head->next;
	}
}

void	ft_init_parse(t_parse **head)
{
	(*head)->str = "";
	(*head)->op = 0;
	(*head)->pipe_flag = 0;
	(*head)->cmd = NULL;
}

void	ft_addback_parse(t_parse **head_ref, char *str, int nbr, int *pipe_flag)
{
	t_parse	*newNode;
	t_parse	*last;

	last = *head_ref;
	newNode = malloc(sizeof(t_parse));
	ft_init_parse(&newNode);
	newNode->str = str;
	newNode->op = nbr;
	if (pipe_flag)
	{
		newNode->pipe_flag = *pipe_flag;
		*pipe_flag = 0;
	}
	newNode->next = NULL;
	if (*head_ref == NULL)
	{
		*head_ref = newNode;
		newNode->prev = NULL;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	newNode->prev = last;
	last->next = newNode;
	return ;
}

size_t	len(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_is_builtin_new(char *line)
{
	if (ft_strncmp(line, "echo", len(line)) == 0 && (len(line) == 4))
		return (EXIT_SUCCESS);
	else if (ft_strncmp(line, "pwd", len(line)) == 0 && (len(line) == 3))
		return (EXIT_SUCCESS);
	else if (ft_strncmp(line, "cd", len(line)) == 0 && (len(line) == 2))
		return (EXIT_SUCCESS);
	else if (ft_strncmp(line, "export", len(line)) == 0 && (len(line) == 6))
		return (EXIT_SUCCESS);
	else if (ft_strncmp(line, "unset", len(line)) == 0 && (len(line) == 5))
		return (EXIT_SUCCESS);
	else if (ft_strncmp(line, "env", len(line)) == 0 && (len(line) == 3))
		return (EXIT_SUCCESS);
	else if (ft_strncmp(line, "exit", len(line)) == 0 && (len(line) == 4))
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}
