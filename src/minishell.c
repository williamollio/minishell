#include "../includes/minishell.h"

void ft_sigint(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	else if (signal == SIGSEGV) // ??
		exit(EXIT_FAILURE);
}

int main(int argc, char **argv, char **envp)
{
	char		*line;
	char		**arr;
	t_env_list	*env_head;
	t_parse		*parse;
	int			fd_in_old = -1;
	int			fd_out_old = -1;

	fd_in_old = dup(0);
	fd_out_old = dup(1);
	ft_init(argc, argv, envp, &env_head);
	while (1)
	{
		dup2(fd_in_old, 0);
		dup2(fd_out_old, 1);
		signal(SIGINT, &ft_sigint);
		signal(SIGQUIT, SIG_IGN); // ctrl + slash
		line = readline(ft_strjoin(getenv("USER"), "\x1b[35m @minishell \x1b[0m>> "));
		if (line == NULL)
			exit(EXIT_SUCCESS);
		arr = ft_parsing(envp, line, &parse);
		add_history(line);
		ft_execution(parse, envp, &env_head);
		// ft_print_list_parse(&parse);
		ft_free_list_parse(&parse);
		// ft_free2(arr);
	}
	return (0);
}
