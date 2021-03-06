/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_seperator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wollio <wollio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:42:01 by wollio            #+#    #+#             */
/*   Updated: 2021/11/23 16:53:53 by wollio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_create_cmd(char **split, int count)
{
	int		s;
	int		i;
	char	**cmd;

	s = 1;
	i = 0;
	cmd = malloc(sizeof(char *) * (count + 1));
	while (split[s])
	{
		cmd[i] = ft_strdup(split[s]);
		i++;
		s++;
	}
	cmd[i] = NULL;
	return (cmd);
}

void	ft_flip_nodes(t_parse **parse, t_parse *temp)
{
	if (temp->next == NULL)
	{
		temp->prev->next = temp->next;
		temp->next = temp->prev;
		*parse = temp;
		temp->prev = NULL;
	}
	else if (*parse == temp->prev)
	{
		temp->prev->next = temp->next;
		temp->next = temp->prev;
		*parse = temp;
		temp->prev = NULL;
		temp->next->prev = temp;
		temp->next->next->prev = temp->next;
	}
	else
	{
		temp->prev->next = temp->next;
		temp->next = temp->prev;
		temp->prev->prev->next = temp;
		temp->prev = temp->next->prev;
		temp->next->prev = temp;
		temp->next->next->prev = temp->next;
	}
}

int	ft_special(t_parse **parse, char **split, t_parse *temp)
{
	char	*str;
	int		i;

	if (split[1] != NULL && *parse != temp
		&& (temp->prev->op == CMD || temp->prev->op == PIPE)
		&& temp->pipe_flag == 0)
	{
		str = ft_strdup(temp->prev->str);
		if (ft_strncmp(temp->prev->str, "", 1) == 0)
			return (0);
		free(temp->prev->str);
		i = 1;
		while (split[i])
		{
			ft_append(&str, &split[i]);
			i++;
		}
		temp->prev->str = str;
		ft_flip_nodes(parse, temp);
		return (0);
	}
	return (1);
}

int	ft_special_2(char **split, t_parse **parse, t_parse *temp)
{
	if (split[1] == NULL && *parse != temp
		&& (temp->prev->op == CMD || temp->prev->op == PIPE)
		&& (temp->op == IN || temp->op == LEFT))
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

void	ft_seperator(t_parse **parse)
{
	t_parse	*temp;
	char	**split;
	char	**cmd;
	int		count;

	count = 0;
	temp = *parse;
	while (temp != NULL)
	{
		if (temp->op >= 2 && temp->op <= 5)
		{
			split = ft_split2(temp->str, ' ', &count);
			ft_free1(temp->str);
			temp->str = ft_strdup(split[0]);
			if (split[1] != NULL && ft_special(parse, split, temp))
			{
				cmd = ft_create_cmd(split, count);
				ft_add_next(parse, temp, cmd, CMD);
			}
			else if (!ft_special_2(split, parse, temp))
				ft_flip_nodes(parse, temp);
			ft_free2(split);
		}
		temp = temp->next;
	}
}
