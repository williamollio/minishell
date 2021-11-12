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
			perror((*parse)->str);
			return (1);
		}
		if ((*parse)->next->op != IN && (*parse)->next->op != LEFT)
			exec->temp_fd = dup(exec->infile);
		close(exec->infile);
	}
	else if ((*parse)->op == LEFT)
		ft_heredoc(exec, *parse);
	else
	{
		exec->temp_fd = dup(STDIN_FILENO);
		exec->breakout = 1;
	}
	return (0);
}

// for now only first outfile
void	ft_redirect_out(t_exec *exec, t_parse *parse)
{
	if (parse->next == NULL)
	{
		dup2(exec->stout, STDOUT_FILENO);
		close(exec->stout);
		close(exec->pipes[1]);
		return ;
	}
	else if (parse->next->op == PIPE)
	{
		dup2(exec->pipes[1], STDOUT_FILENO);
		close(exec->pipes[1]);
	}
	else if(parse->next->op == OUT)
	{
		exec->outfile = open(parse->next->cmd[0], O_RDWR | O_CREAT | O_TRUNC, 0777);
		dup2(exec->outfile, 1);
		close(exec->outfile);
		close(exec->pipes[1]);
	}
	else if(parse->next->op == RIGHT)
	{
		exec->outfile = open(parse->next->cmd[0], O_RDWR | O_CREAT | O_APPEND, 0777);
		dup2(exec->outfile, 1);
		close(exec->outfile);
		close(exec->pipes[1]);
	}
}
