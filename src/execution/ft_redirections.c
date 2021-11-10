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
		exec->infile = open((*parse)->str, 0);
		if (exec->infile == -1)
		{
			perror((*parse)->str);
			return (1);
		}
		exec->temp_fd = dup(exec->infile);
		close(exec->infile);
		*parse = (*parse)->next;
	}
	else if ((*parse)->op == LEFT)
	{
		ft_heredoc(exec, *parse);
		*parse = (*parse)->next;
	}
	else
		exec->temp_fd = dup(STDIN_FILENO);
	return (0);
}

void	ft_redirect_out(t_exec *exec, t_parse *parse)
{
	if (parse->op == 0) // if its the last command and no outfile exists
	{
		dup2(exec->stout, STDOUT_FILENO);
		close(exec->stout);
		close(exec->pipes[1]);
	}
	else if (parse->op == PIPE) // if its not the last command
	{
		dup2(exec->pipes[1], STDOUT_FILENO);
		close(exec->pipes[1]);
	}
	else if(parse->op == OUT) // if its the last command and outfile exists
	{
		exec->outfile = open(parse->next->str, O_RDWR | O_CREAT | O_TRUNC, 0777);
		dup2(exec->outfile, 1);
		close(exec->outfile);
		close(exec->pipes[1]);
	}
	else if(parse->op == RIGHT) // if its the last command and outfile exists
	{
		exec->outfile = open(parse->next->str, O_RDWR | O_CREAT | O_APPEND, 0777);
		dup2(exec->outfile, 1);
		close(exec->outfile);
		close(exec->pipes[1]);
	}
}
