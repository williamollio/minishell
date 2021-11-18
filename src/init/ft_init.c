#include "../../includes/minishell.h"

void	ft_silience(char **envp)
{
	pid_t	childpid;
	char	**cmd;

	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = "stty";
	cmd[1] = "-echoctl";
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

void	ft_init(int argc, char **argv, char **envp, t_env **env_head)
{
	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("minishell : no arguments accepted\n", 2);
		exit(EXIT_FAILURE);
	}
	clear();
	ft_silience(envp);
	ft_get_env_list(envp, env_head);
}

void	ft_sigint(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
}
