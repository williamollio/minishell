/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wollio <wollio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:42:01 by wollio            #+#    #+#             */
/*   Updated: 2021/11/18 18:51:44 by wollio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_append(char **last_arg, char **arg)
{
	char	*temp;

	if (ft_strncmp(*last_arg, "", 1) == 0)
		*last_arg = *arg;
	else
	{
		temp = ft_strjoin(*last_arg, " ");
		ft_free1(*last_arg);
		*last_arg = temp;
		temp = ft_strjoin(*last_arg, *arg);
		ft_free1(*last_arg);
		*last_arg = temp;
	}
}
