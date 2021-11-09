#include "../../includes/minishell.h"

void	ft_heredoc(t_exec *exec, t_parse *test)
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
		if (line == NULL)
			break ;
		if (ft_strncmp(test->str, line, ft_strlen(test->str)) == 0 && ft_strlen(line) == ft_strlen(test->str))
			break ;
		ft_putendl_fd(line, fd[1]);
	}
	exec->temp_fd = dup(fd[0]);
	close(fd[0]);
	close(fd[1]);
}