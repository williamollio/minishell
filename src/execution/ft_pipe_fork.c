/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wollio <wollio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:42:01 by wollio            #+#    #+#             */
/*   Updated: 2021/11/18 18:50:48 by wollio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pipe(t_exec *exec)
{
	if (pipe(exec->pipes) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

int	ft_fork(t_exec *exec)
{
	exec->pid = fork();
	if (exec->pid == -1)
	{
		perror("fork");
		return (-2);
	}
	return (exec->pid);
}
