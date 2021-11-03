#include "../../includes/minishell.h"

void	ft_pipe(t_exec *exec)
{
	if (pipe(exec->pipes) == -1)
	{
		perror("pipe");
		exit(0);
	}
}

void	ft_fork(t_exec *exec)
{
	exec->pid = fork();
	if (exec->pid == -1)
	{
		perror("fork");
		exit(0);
	}
}
