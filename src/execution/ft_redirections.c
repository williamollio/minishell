/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wollio <wollio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:42:01 by wollio            #+#    #+#             */
/*   Updated: 2021/11/18 18:50:52 by wollio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_parent(t_exec *exec)
{
	close(exec->temp_fd);
	dup2(exec->pipes[0], exec->temp_fd);
	close(exec->pipes[0]);
}

void	ft_in_is_tempfd(t_exec *exec)
{
	dup2(exec->temp_fd, STDIN_FILENO);
	close(exec->temp_fd);
}

int	ft_infile(t_exec *exec, t_parse **parse)
{
	exec->infile = open((*parse)->cmd[0], 0);
	if (exec->infile == -1)
	{
		perror((*parse)->cmd[0]);
		return (-1);
	}
	if ((*parse)->next == NULL)
	{
		close(exec->temp_fd);
		close(exec->infile);
		return (1);
	}
	if ((*parse)->next->op != IN && (*parse)->next->op != LEFT)
	{
		close(exec->temp_fd);
		exec->temp_fd = dup(exec->infile);
	}
	close(exec->infile);
	return (1);
}

int	ft_redirect_in(t_exec *exec, t_parse **parse)
{
	if ((*parse)->op == IN)
	{
		if (ft_infile(exec, parse) == -1)
			return (-1);
		else
			return (1);
	}
	else if ((*parse)->op == LEFT)
	{
		close(exec->temp_fd);
		if (ft_heredoc(exec, *parse) == -1)
			return (-1);
		else
			return (1);
	}
	return (0);
}

void	ft_write_to_pipe(t_exec *exec)
{
	dup2(exec->pipes[1], STDOUT_FILENO);
	close(exec->pipes[1]);
}
