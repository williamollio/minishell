#include "../../includes/minishell.h"

int	ft_open_outfile(t_exec *exec, t_parse *parse)
{
	if (parse->op == OUT)
	{
		exec->outfile = open(parse->cmd[0], O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (exec->outfile == -1)
		{
			perror(parse->cmd[0]);
			return (-1);
		}
		close(exec->pipes[1]);
	}
	if (parse->op == RIGHT)
	{
		exec->outfile = open(parse->cmd[0], O_RDWR | O_CREAT | O_APPEND, 0777);
		if (exec->outfile == -1)
		{
			perror(parse->cmd[0]);
			return (-1);
		}
		close(exec->pipes[1]);
	}
	return (0);
}

int	ft_choose_outfile(t_exec *exec, t_parse *parse)
{
	while (parse != NULL)
	{
		if (ft_open_outfile(exec, parse) == -1)
			return (-1);
		parse = parse->next;
		if (parse == NULL)
		{
			dup2(exec->outfile, 1);
			close(exec->outfile);
			return (1);
		}
		else if (parse->op != OUT && parse->op != RIGHT)
		{
			dup2(exec->outfile, 1);
			close(exec->outfile);
			return (2);
		}
		else
			close(exec->outfile);
	}
	return (0);
}

int	ft_write_here(t_parse *parse, t_exec *exec)
{
	if (parse->next != NULL)
	{
		if (parse->next->op == PIPE || parse->next->pipe_flag == PIPE)
		{
			ft_write_to_pipe(exec);
		}
		if (parse->next->op == OUT || parse->next->op == RIGHT)
		{
			exec->out_action = ft_choose_outfile(exec, parse);
			if (exec->out_action == -1)
				return (-1);
		}
	}
	else
	{
		dup2(exec->stout, STDOUT_FILENO);
		close(exec->stout);
	}
	return (0);
}

int	ft_file_only_in(t_parse *parse, t_exec *exec)
{
	exec->infile = open(parse->cmd[0], 0);
	if (exec->infile == -1)
	{
		perror(parse->cmd[0]);
		return (-1);
	}
	if (parse->next == NULL)
	{
		close(exec->temp_fd);
		return (0);
	}
	if (parse->next->op != IN && parse->next->op != LEFT)
	{
		close(exec->temp_fd);
		dup2(exec->infile, exec->temp_fd);
	}
	close(exec->infile);
	return (0);
}

int	ft_file_only(t_parse *parse, t_exec *exec)
{
	while (parse != NULL)
	{
		if (parse->op == IN || parse->op == LEFT)
		{
			if (parse->op == IN)
			{
				if (ft_file_only_in(parse, exec) == -1)
					return (-1);
			}
			else if (parse->op == LEFT)
			{
				close(exec->temp_fd);
				ft_heredoc(exec, parse);
			}
		}
		else
			if (ft_choose_outfile(exec, parse) == -1)
				return (-1);
		parse = parse->next;
	}
	return (0);
}
