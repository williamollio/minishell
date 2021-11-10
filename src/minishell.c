#include "../includes/minishell.h"

int	exit_status;

int main(int argc, char **argv, char **envp)
{
	char		*line;
	t_env_list	*env_head;
	t_parse		*parse;
	int			fd_in_old = -1;
	int			fd_out_old = -1;

	fd_in_old = dup(0);
	fd_out_old = dup(1);
	ft_init(argc, argv, envp, &env_head);
	while (1)
	{
		//ft_tool(&fd_in_old, &fd_out_old);
		dup2(fd_in_old, 0);
		dup2(fd_out_old, 1);
		signal(SIGINT, &ft_sigint);
		signal(SIGQUIT, SIG_IGN);
		line = readline(ft_strjoin(getenv("USER"), "\x1b[35m @minishell \x1b[0m>> "));
		if (line == NULL)
			exit(EXIT_SUCCESS);
		if ((ft_strncmp(ft_strtrim(line, " "), "\n", 1) && ft_strlen(ft_strtrim(line, " "))) && !ft_parsing(envp, line, &parse))
		{
			ft_print_list_parse(&parse);
			//ft_execution(parse, envp, &env_head);
		}
		add_history(line);
		ft_free_list_parse(&parse);
	}
	return (0);
}
