/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurz <akurz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 17:07:03 by akurz             #+#    #+#             */
/*   Updated: 2021/10/25 15:27:38 by akurz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_var(char *full)
{
	int		x;
	char	*var;

	x = 0;
	while (full[x] != '=')
	x++;
	var = ft_substr(full, 0, x);
	return (var);
}

char	*ft_get_content(char *full)
{
	int		x;
	char	*con;

	x = 0;
	while (full[x] != '=')
	x++;
	con = ft_substr(full, x + 1, ft_strlen(full) - x);
	return (con);
}

void	ft_addback(t_env_list **head_ref, char *str)
{
	t_env_list	*newNode;
	t_env_list	*last;

	last = *head_ref;
	newNode = malloc(sizeof(t_env_list));
	newNode->full = str;
	newNode->var = ft_get_var(str);
	newNode->content = ft_get_content(str);
	newNode->next = NULL;
	if (*head_ref == NULL)
	{
		*head_ref = newNode;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = newNode;
	return ;
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

void	ft_print_list(t_env_list *head)
{
	while (head != NULL)
	{
		printf("%s\n", head->full);
		head = head->next;
	}
}

void	ft_get_env_list(char **envp, t_env_list **env_head)
{
	int	x;

	x = 0;
	while (envp[x])
	{
		ft_addback(env_head, envp[x]);
		x++;
	}
	return ;
}