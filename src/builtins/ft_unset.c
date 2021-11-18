/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wollio <wollio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:42:01 by wollio            #+#    #+#             */
/*   Updated: 2021/11/18 18:50:09 by wollio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_remove(t_env *temp, char *str)
{
	t_env	*prev;

	while (ft_strncmp(temp->next->var, str, ft_strlen(temp->next->var)) != 0
		|| ft_strlen(temp->next->var) != ft_strlen(str))
	{
		temp = temp->next;
		if (temp->next == NULL)
			return ;
	}
	prev = temp;
	temp = temp->next;
	prev->next = temp->next;
	free(temp->var);
	free(temp->full);
	free(temp->content);
	free(temp);
}

void	ft_delete_node(t_env **env_head, char *str)
{
	t_env	*temp;

	if (ft_strncmp(str, "_", ft_strlen(str)) == 0)
		return ;
	temp = *env_head;
	if (temp == NULL)
		return ;
	if (ft_strncmp((*env_head)->var, str, ft_strlen((*env_head)->var)) == 0
		&& ft_strlen((*env_head)->var) == ft_strlen(str))
	{
		(*env_head) = (*env_head)->next;
		free(temp->var);
		free(temp->full);
		free(temp->content);
		free(temp);
	}
	else
		ft_remove(temp, str);
}

void	ft_unset_node(t_env **env_head, char **cmd)
{
	int		i;

	g_exit_status = 0;
	i = 1;
	while (cmd[i])
	{
		ft_delete_node(env_head, cmd[i]);
		i++;
	}
	return ;
}
