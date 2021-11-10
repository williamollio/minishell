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
	exec->waitcount = 0;
	exec->child_status = 0;
}

int	ft_count_cmds(t_parse *test)
{
	int	count;

	count = 0;
	while (test != NULL)
	{
		if (test->flag == SYS || test->flag == BUILT)
			count++;
		test = test->next;
	}
	return (count);
}

void	ft_exec_multiple(t_parse *test, char **envp, t_env_list **env_head, t_exec *exec)
{
	exec->waitcount++;
	ft_fork(exec);
	if (test->flag == SYS && exec->pid == 0)
	{
		close(exec->pipes[1]);
		close(exec->pipes[0]);
		ft_child_for_sys(test, envp, env_head);
	}
	if (test->flag == BUILT && exec->pid == 0)
	{
		close(exec->pipes[1]);
		close(exec->pipes[0]);
		ft_child_for_built(test, env_head, EX);
	}
	else
	{
		close(exec->pipes[1]);
		ft_parent(exec);
	}
}

void	ft_execution(t_parse *test, char **envp, t_env_list **env_head) // now i segfault if i have no commands, beause while loop statement has changed
{
	t_exec	exec;

	ft_init_exec(&exec);
	if (!test)
		return ;
	while (1) // only use last infile when there are multiple
	{
		if (test->next == NULL)
			break ;
		if (test->next->flag != FILE || test->flag != FILE)
			break ;
		test = test->next;
	}
	if (ft_redirect_in(&exec, &test) == 1)
		return ;
	exec.cmdcount = ft_count_cmds(test);
	// the while loop conditions is bad. If there are multiple outfiles, i need to quit the whileloop,
	// between the next to last and last node. I also need to open all outfiles but only write to the last one.
	// its also possible that there are more commands coming after an outfile.
	// Need to communicate this with william
	while (test != NULL && test->flag != FILE) // (test != NULL && test->flag != FILE)
	{
		ft_pipe(&exec);
		ft_in_is_tempfd(&exec);
		ft_redirect_out(&exec, test);
		if (exec.cmdcount == 1 && test->flag == BUILT)
		{
			ft_child_for_built(test, env_head, RET);
			ft_parent(&exec);
		}
		else if (test->flag == SYS || test->flag == BUILT)
			ft_exec_multiple(test, envp, env_head, &exec);
		else
			ft_parent(&exec);
		test = test->next;
	}
	while (exec.waitcount > 0)
	{
		waitpid(0, &exec.child_status, 0);
		if (WIFEXITED(exec.child_status))
			exit_status = WEXITSTATUS(exec.child_status);
		exec.waitcount--;
	}
	ft_close_all(&exec);
	return ;
}
