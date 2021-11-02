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

void ft_readinput(char *line, char **envp, t_env_list **env_head)
{
	char **onlyForNow;
	char *improvised_parse; //weird edgecase with space

	if (ft_strncmp(line, "echo", 4) == 0)
		ft_echo(line);
	else if (ft_strncmp(line, "export", 6) == 0)
	{
		onlyForNow = ft_split(line, ' ');
		// ft_export_node(env_head, onlyForNow[1]); //normal
		improvised_parse = ft_strjoin(onlyForNow[1], " ");
		improvised_parse = ft_strjoin(improvised_parse, onlyForNow[2]);
		ft_export_node(env_head, improvised_parse); //weird edgecase with space
	}
	else if (ft_strncmp(line, "unset", 5) == 0)
	{
		onlyForNow = ft_split(line, ' ');
		// ft_delete_node(env_head, onlyForNow[1]); //normal
		improvised_parse = ft_strjoin(onlyForNow[1], " ");
		improvised_parse = ft_strjoin(improvised_parse, onlyForNow[2]);
		ft_unset_node(env_head, improvised_parse); //edgecase with space
	}
	else if (ft_strncmp(line, "env", 3) == 0)
		ft_print_list(*env_head);
	else if (ft_strncmp(line, "exit", 4) == 0)
		ft_exit();
	else if (ft_strncmp(line, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(line, "cd", 2) == 0)
		ft_cd(env_head, line);
	else
		ft_error(line);
	(void)envp;
	return ;
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
		dup2(fd_in_old, 0); //needed, otherwise the outout from ft_sys_func gets written into readline --> infinite loop
		dup2(fd_out_old, 1);
		signal(SIGINT, &ft_sigint);
		signal(SIGQUIT, SIG_IGN); // ctrl + slash
		line = readline(ft_strjoin(getenv("USER"), "\x1b[35m @minishell \x1b[0m>> "));
		if (line == NULL)
			exit(EXIT_SUCCESS);
		arr = ft_parsing(envp, line, &parse);
		add_history(line);
		ft_execution(parse, envp, &env_head);
		//ft_print_list_parse(&parse);
		ft_free_list_parse(&parse);
		ft_free2(arr);
	}
	return (0);
}
