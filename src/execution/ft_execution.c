#include "../../includes/minishell.h"

void	ft_exec_multiple(t_parse *parse, char **envp, t_env_list **env_head, t_exec *exec)
{
	exec->waitcount++;
	ft_fork(exec);
	if (ft_is_builtin_new(parse->cmd[0]) && exec->pid == 0)
	{
		close(exec->pipes[1]);
		close(exec->pipes[0]);
		ft_child_for_sys(parse, envp, env_head);
	}
	else if (!ft_is_builtin_new(parse->cmd[0]) && exec->pid == 0)
	{
		close(exec->pipes[1]);
		close(exec->pipes[0]);
		ft_child_for_built(parse, env_head, EX);
	}
	else
	{
		close(exec->pipes[1]);
		ft_parent(exec);
	}
}

void	ft_execution(t_parse *parse, char **envp, t_env_list **env_head)
{
	t_exec	exec;

	ft_init_exec(&exec, parse);
	if (!parse)
		return ;
	if (ft_set_infile(&exec, &parse) == 1) // call  it in the loop
		return ; // not sure if i stll nedd to execute the other shit
	while (parse != NULL)
	{
		ft_pipe(&exec);
		ft_in_is_tempfd(&exec);
		ft_redirect_out(&exec, parse);
		if (exec.cmdcount == 1 && !ft_is_builtin_new(parse->cmd[0]))
		{
			ft_child_for_built(parse, env_head, RET);
			ft_parent(&exec);
		}
		else if (parse->op == CMD || parse->op == PIPE)
			ft_exec_multiple(parse, envp, env_head, &exec);
		else
			ft_parent(&exec);
		parse = parse->next;
	}
	ft_wait(exec);
	ft_close_all(&exec);
}
