/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_system.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wollio <wollio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:42:01 by wollio            #+#    #+#             */
/*   Updated: 2021/11/23 17:40:08 by wollio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_countrows(char **paths)
{
	int	i;

	i = 0;
	while (paths[i] != NULL)
		i++;
	return (i);
}

char	*ft_check_commandpath(int rows, char **paths, char *cmd)
{
	int		i;
	char	*ret;
	char	*slash;

	i = 0;
	if (cmd[0] == '/' || cmd[0] == '.')
		return (ft_strdup(cmd));
	while (i <= rows)
	{
		slash = ft_strjoin(paths[i], "/");
		ret = ft_strjoin(slash, cmd);
		ft_free1(slash);
		if (access(ret, F_OK) != -1)
			return (ret);
		free(ret);
		i++;
	}
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

void	ft_execute_child(t_sys *sys, t_parse *parse, char **envp)
{
	if (sys->pathname == NULL)
	{
		if (execve(parse->cmd[0], parse->cmd, envp) == -1)
		{
			perror(parse->cmd[0]);
			exit(126);
		}
	}
	sys->paths = ft_split(sys->pathname, ':');
	ft_free1(sys->pathname);
	sys->rows = ft_countrows(sys->paths);
	sys->cmdpath = ft_check_commandpath(sys->rows, sys->paths, parse->cmd[0]);
	ft_free2(sys->paths);
	if (parse->cmd[0][0] == '/' || parse->cmd[0][0] == '.')
	{
		sys->split2 = ft_split(parse->cmd[0], '/');
		sys->rows = ft_countrows(sys->split2);
		ft_free2(sys->split2);
	}
	if (execve(sys->cmdpath, parse->cmd, envp) == -1)
	{
		perror(parse->cmd[0]);
		ft_free1(sys->cmdpath);
		exit(126);
	}
}

void	ft_child_for_sys(t_parse *parse, char **envp, t_env **env_head)
{
	t_sys	sys;

	sys.rows = 0;
	sys.pathname = ft_extract_content(*env_head, "PATH");
	if (sys.pathname != NULL || (parse->cmd[0][0] == '/' || parse->cmd[0][0] == '.'))
		ft_execute_child(&sys, parse, envp);
	else
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(parse->cmd[0], 2);
		ft_putendl_fd(": No such file or directory", 2);
		ft_free1(sys.pathname);
		exit(127);
	}
}
