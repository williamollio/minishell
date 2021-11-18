#include "../../includes/minishell.h"

int	ft_variable_pid(int pid)
{
	static int	pid_2 = 0;

	if (pid == -2)
		return (-1);
	if (pid != -1)
		pid_2 = pid;
	return (pid_2);
}

int	ft_exec_multiple(t_parse *pars, char **envp, t_env **env, t_exec *exec)
{
	exec->waitcount++;
	signal(SIGINT, sigfunc_child);
	signal(SIGQUIT, sigfunc_child);
	if (ft_variable_pid(ft_fork(exec)) == -1)
		return (-1);
	if (ft_is_builtin_new(pars->cmd[0]) && exec->pid == 0)
	{
		close(exec->pipes[1]);
		close(exec->pipes[0]);
		ft_child_for_sys(pars, envp, env);
	}
	else if (!ft_is_builtin_new(pars->cmd[0]) && exec->pid == 0)
	{
		close(exec->pipes[1]);
		close(exec->pipes[0]);
		ft_child_for_built(pars, env, EX);
	}
	else
	{
		close(exec->pipes[1]);
		ft_parent(exec);
	}
	return (0);
}

int	ft_skip_outfiles(t_parse **parse, t_exec *exec)
{
	if (exec->out_action == 1)
		return (0);
	if (exec->out_action == 2)
	{
		while ((*parse)->next->op == OUT || (*parse)->next->op == RIGHT)
			*parse = (*parse)->next;
		exec->out_action = 0;
	}
	return (1);
}

int	ft_core(t_parse **parse, t_exec *exec, char **envp, t_env **env_head)
{
	if (ft_pipe(exec) == -1)
		return (-1);
	ft_in_is_tempfd(exec);
	if (ft_write_here(*parse, exec) == -1)
		return (-1);
	if (exec->cmdcount == 1 && !ft_is_builtin_new((*parse)->cmd[0]))
	{
		ft_child_for_built(*parse, env_head, RET);
		ft_parent(exec);
	}
	else if ((*parse)->op == CMD || (*parse)->op == PIPE)
	{
		if (ft_exec_multiple(*parse, envp, env_head, exec) == -1)
			return (-1);
	}
	else
		ft_parent(exec);
	return (0);
}

void	ft_execution(t_parse *parse, char **envp, t_env **env_head)
{
	t_exec	exec;

	ft_init_exec(&exec, parse);
	if (ft_catch_trash(parse, &exec) == -1)
	{
		ft_close_all(&exec);
		return ;
	}
	while (parse != NULL)
	{
		exec.ret = ft_redirect_in(&exec, &parse);
		if (exec.ret == -1)
			break ;
		if (exec.ret == 0)
		{
			if (ft_core(&parse, &exec, envp, env_head) == -1)
				break ;
			if (!ft_skip_outfiles(&parse, &exec))
				break ;
		}
		parse = parse->next;
	}
	ft_wait(exec);
	ft_close_all(&exec);
}
