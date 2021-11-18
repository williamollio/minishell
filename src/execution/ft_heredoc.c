#include "../../includes/minishell.h"

int	ft_flag(int flag)
{
	static int	flag_2 = 0;

	if (flag != -1)
		flag_2 = flag;
	return (flag_2);
}

void	ft_sigint2(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "Hit ENTER to go back to shell!", 31);
		ft_flag(1);
		return ;
	}
}

int	ft_heredoc_loop(t_parse *parse, int	(*fd)[2])
{
	char	*line;

	signal(SIGINT, ft_sigint2);
	if (ft_flag(-1))
	{
		ft_flag(0);
		close((*fd)[0]);
		close((*fd)[1]);
		return (-1);
	}
	line = readline("\x1b[35m>>> \x1b[0m");
	if (line == NULL)
		return (1);
	if (ft_strncmp(parse->cmd[0], line, ft_strlen(parse->cmd[0])) == 0
		&& ft_strlen(line) == ft_strlen(parse->cmd[0]))
		return (1);
	ft_putendl_fd(line, (*fd)[1]);
	return (0);
}

int	ft_heredoc(t_exec *exec, t_parse *parse)
{
	int		fd[2];
	int		ret;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	while (1)
	{
		ret = ft_heredoc_loop(parse, &fd);
		if (ret == 1)
			break ;
		if (ret == -1)
			return (0);
	}
	if (parse->next == NULL)
		exec->temp_fd = dup(fd[0]);
	else if (parse->next->op != IN && parse->next->op != LEFT)
		exec->temp_fd = dup(fd[0]);
	close(fd[0]);
	close(fd[1]);
	return (0);
}
