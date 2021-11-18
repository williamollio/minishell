/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wollio <wollio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:42:01 by wollio            #+#    #+#             */
/*   Updated: 2021/11/18 18:49:44 by wollio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_env *env_head)
{
	char	*path_existence;

	path_existence = ft_extract_content(env_head, "PATH");
	if (path_existence == NULL)
	{
		g_exit_status = 127;
		ft_putendl_fd("bash: env: No such file or directory", 2);
	}
	else
	{
		g_exit_status = 0;
		ft_print_list(env_head);
	}
	free(path_existence);
}
