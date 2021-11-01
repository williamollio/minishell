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
	int	i;
	char **onlyForNow;
	i = 0;
	while (line[i])
	{
		if (ft_strncmp(&line[i], "echo", 4) == 0)
		{
			ft_echo(line);
			return ;
		}
		else if (ft_strncmp(line, "export", 6) == 0)
		{
			onlyForNow = ft_split(line, ' ');
			ft_export_node(env_head, onlyForNow[1]);
			return ;
		}
		else if (ft_strncmp(line, "unset", 5) == 0)
		{
			onlyForNow = ft_split(line, ' ');
			ft_delete_node(env_head, onlyForNow[1]);
			return ;
		}
		else if (ft_strncmp(&line[i], "env", 3) == 0)
		{
			// ft_env(envp);
			ft_print_list(*env_head);
			return ;
		}
		else if (ft_strncmp(&line[i], "exit", 4) == 0)
			ft_exit();
		// else if (ft_strncmp(line, "cd", 2))
		// 	ft_cd(line);
		// else if (ft_strncmp(line, "pwd", 3))
		// 	ft_pwd(line);
		// else if (ft_sys_func_chck(line))
		// 	ft_sys_func_ex(line);
		i++;
	}
	(void)envp;
	//ft_error(line);
	return ;
}

int main(int argc, char **argv, char **envp)
{
	char		*line;
	char		**arr;
	t_env_list	*env_head;
	t_parse		*parse;

	ft_init(argc, argv, envp, &env_head);
	while (1)
	{
		signal(SIGINT, &ft_sigint);
		signal(SIGQUIT, SIG_IGN); // ctrl + slash
		line = readline(ft_strjoin(getenv("USER"), "\x1b[35m @minishell \x1b[0m>> "));
		if (line == NULL)
			exit(EXIT_SUCCESS);
		arr = ft_parsing(envp, line, &parse);
		add_history(line);
		//ft_readinput(line, envp, &env_head);
		ft_print_list_parse(parse);
		ft_free_list_parse(&parse);
		ft_free2(arr);
	}
	return (0);
}
