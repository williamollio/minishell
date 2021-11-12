#include "../../includes/minishell.h"

void	ft_close_all(t_exec *exec)
{
	close(exec->pipes[0]);
	close(exec->pipes[1]);
	close(exec->temp_fd);
	close(exec->infile);
	close(exec->outfile);
	close(exec->stout);
	close(STDIN_FILENO);
}

int	ft_count_cmds(t_parse *parse)
{
	int	count;

	count = 0;
	while (parse != NULL)
	{
		if (parse->op == CMD || parse->op == PIPE)
			count++;
		parse = parse->next;
	}
	return (count);
}

void	ft_init_exec(t_exec *exec, t_parse *parse)
{
	exec->pipes[0] = -1;
	exec->pipes[1] = -1;
	exec->pid = -1;
	exec->temp_fd = -1;
	exec->stout = dup(STDOUT_FILENO);
	exec->outfile = -1;
	exec->infile = -1;
	exec->cmdcount = ft_count_cmds(parse);
	exec->waitcount = 0;
	exec->child_status = 0;
	exec->breakout = 0;
}

int	ft_set_infile(t_exec *exec, t_parse **parse)
{
	while (1)
	{
		if (ft_redirect_in(exec, parse) == 1)
			return (1);
		if (exec->breakout == 1)
			break ;
		*parse = (*parse)->next;
		if ((*parse)->next == NULL)
			break ;
		if ((*parse)->op != IN && (*parse)->op != LEFT)
			break ;
	}
	return (0);
}

void	ft_wait(t_exec exec)
{
	while (exec.waitcount > 0)
	{
		waitpid(0, &exec.child_status, 0);
		if (WIFEXITED(exec.child_status))
			exit_status = WEXITSTATUS(exec.child_status);
		exec.waitcount--;
	}
}
