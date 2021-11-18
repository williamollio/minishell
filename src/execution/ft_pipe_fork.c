#include "../../includes/minishell.h"

int	ft_pipe(t_exec *exec)
{
	if (pipe(exec->pipes) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

int	ft_fork(t_exec *exec)
{
	exec->pid = fork();
	if (exec->pid == -1)
	{
		perror("fork");
		return (-2);
	}
	return (exec->pid);
}
