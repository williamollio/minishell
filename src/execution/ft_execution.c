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

void	ft_init_exec(t_exec *exec)
{
	exec->pipes[0] = -1;
	exec->pipes[1] = -1;
	exec->pid = -1;
	exec->temp_fd = -1;
	exec->stout = dup(STDOUT_FILENO);
	exec->outfile = -1;
	exec->infile = -1;
	exec->cmdcount = 0;
}

// path to opening infile might be different, depending how william parses input
void	ft_execution(t_parse *test, char **envp, t_env_list **env_head)
{
	t_exec	exec;

	ft_init_exec(&exec);
	if (!test)
		return ;
	if (ft_redirect_in(&exec, &test) == 1)
		return ;
	while (test != NULL && test->flag != FILE)
	{
		// if (keine pipe vor oder nach nem command, exec built in main)
		// else (muss auch fuer builtins forken um das command im child zu executen)
		// because of case export test=test | env  for.example
		ft_pipe(&exec);
		ft_in_is_tempfd(&exec);
		ft_redirect_out(&exec, test);
		if (test->flag == BUILT)
		{
			ft_child_for_built(test, env_head);
			ft_parent(&exec);
		}
		else if (test->flag == SYS)
		{
			ft_fork(&exec);
			if (exec.pid == 0)
			{
				close(exec.pipes[1]);
				close(exec.pipes[0]);
				ft_child_for_sys(test, envp);
			}
			else
			{
				close(exec.pipes[1]);
				wait(NULL);
				ft_parent(&exec);
			}
		}
		test = test->next;
	}
	ft_close_all(&exec);
	return ;
}
