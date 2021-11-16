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

int	ft_redirect_in(t_exec *exec, t_parse **parse)
{
	if ((*parse)->op == IN)
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
	else if ((*parse)->op == LEFT)
	{
		close(exec->temp_fd);
		ft_heredoc(exec, *parse);
		return (1);
	}
	return (0);
}
