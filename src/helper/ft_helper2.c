/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wollio <wollio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:42:01 by wollio            #+#    #+#             */
/*   Updated: 2021/11/18 18:51:04 by wollio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_list(t_env **head_a)
{
	t_env	*tmp;

	while ((*head_a) != NULL)
	{
		tmp = (*head_a);
		(*head_a) = (*head_a)->next;
		free(tmp->full);
		free(tmp);
	}
}

t_parse	*ft_get_last(t_parse **head)
{
	t_parse	*tmp;

	tmp = (*head);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

t_parse	*ft_get_list(t_parse *parse_list)
{
	static t_parse	*list;

	if (parse_list)
		list = parse_list;
	return (list);
}

char	**ft_get_paths(char **paths)
{
	static char	**paths2;

	if (paths != NULL)
		paths2 = paths;
	return (paths2);
}

char	*ft_extract_content(t_env *env_head, char *var)
{
	char	*content;
	int		x;

	while (ft_strncmp(env_head->var, var, ft_strlen(env_head->var)) != 0
		|| (ft_strlen(env_head->var) != ft_strlen(var)))
	{
		env_head = env_head->next;
		if (env_head == NULL)
			return (NULL);
	}
	x = 0;
	while (env_head->full[x] != '=')
		x++;
	content = ft_substr(env_head->full, x + 1, ft_strlen(env_head->full) - x);
	return (content);
}
