/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wollio <wollio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:42:01 by wollio            #+#    #+#             */
/*   Updated: 2021/11/18 18:50:21 by wollio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_child_for_built(t_parse *parse, t_env **env_head, int status)
{
	if (ft_strncmp(parse->cmd[0], "echo", 4) == 0)
		ft_echo(parse->cmd);
	else if (ft_strncmp(parse->cmd[0], "export", 6) == 0)
		ft_export_node(env_head, parse->cmd);
	else if (ft_strncmp(parse->cmd[0], "unset", 5) == 0)
		ft_unset_node(env_head, parse->cmd);
	else if (ft_strncmp(parse->cmd[0], "env", 3) == 0)
		ft_env(*env_head);
	else if (ft_strncmp(parse->cmd[0], "exit", 4) == 0)
		ft_exit(parse);
	else if (ft_strncmp(parse->cmd[0], "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(parse->cmd[0], "cd", 2) == 0)
		ft_cd(env_head, parse->cmd[1]);
	if (status == EX)
		exit(g_exit_status);
	else if (status == RET)
		return ;
}
