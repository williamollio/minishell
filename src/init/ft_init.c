#include "../../includes/minishell.h"

void	ft_silience(char **envp)
{
	int		pipes[2];
	pid_t	childpid;
	char	**cmd;

	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = "stty";
	cmd[1] = "-echoctl";
	if (pipe(pipes) == -1)
	{
		perror("pipe");
		exit(0);
	}
	childpid = fork();
	if (childpid == -1)
	{
		perror("fork");
		exit(0);
	}
	if (childpid == 0)
		execve("/bin/stty", cmd, envp);
	else
	{
		wait(NULL);
		return ;
	}
}

void ft_init(int argc, char **envp, t_env_list **env_head)
{
	clear();
	if (argc != 1)
	{
		ft_putstr_fd("No arguments accepted\n", 2);
		exit(EXIT_FAILURE);
	}
	ft_silience(envp);
	ft_get_env_list(envp, env_head);
}