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
	exec->temp_fd = dup(STDIN_FILENO);
	exec->stout = dup(STDOUT_FILENO);
	exec->stin = dup(STDIN_FILENO);
	exec->outfile = -1;
	exec->infile = -1;
	exec->cmdcount = ft_count_cmds(parse);
	exec->waitcount = 0;
	exec->child_status = 0;
	exec->breakout = 0;
	exec->out_action = 0;
	exec->ret = 0;
}

void	ft_wait(t_exec exec)
{
	int	signaled;

	while (exec.waitcount > 0)
	{
		waitpid(0, &exec.child_status, 0);
		if (WIFEXITED(exec.child_status))
			g_exit_status = WEXITSTATUS(exec.child_status);
		if (WIFSIGNALED(exec.child_status))
			signaled = WTERMSIG(exec.child_status);
		if (signaled == 3)
			ft_putendl_fd("^\\Quit: 3", 1);
		exec.waitcount--;
	}
}

int	ft_catch_trash(t_parse *parse, t_exec *exec)
{
	if (!parse)
		return (-1);
	if (exec->cmdcount == 0)
	{
		ft_file_only(parse, exec);
		return (-1);
	}
	return (0);
}
