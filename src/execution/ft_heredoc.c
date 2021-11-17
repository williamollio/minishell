#include "../../includes/minishell.h"

int flag = 0;

void ft_sigint2(int signal)
{
	if (signal == SIGINT)
	{
		flag = 1;
		return ;
	}
}
void	ft_heredoc(t_exec *exec, t_parse *parse)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(0);
	}
	while (1)
	{
		line = readline("\x1b[35m>>> \x1b[0m");
		signal(SIGINT, &ft_sigint2);
		if (flag)
			break;
		if (line == NULL)
			break ;
		if (ft_strncmp(parse->cmd[0], line, ft_strlen(parse->cmd[0])) == 0 && ft_strlen(line) == ft_strlen(parse->cmd[0]))
			break ;
		ft_putendl_fd(line, fd[1]);
	}
	if (parse->next == NULL) // added later
		exec->temp_fd = dup(fd[0]);
	else if (parse->next->op != IN && parse->next->op != LEFT)
		exec->temp_fd = dup(fd[0]);
	close(fd[0]);
	close(fd[1]);
}
