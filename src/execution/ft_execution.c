#include "../../includes/minishell.h"

void	ft_exec_multiple(t_parse *parse, char **envp, t_env_list **env_head, t_exec *exec)
{
	exec->waitcount++;
	ft_fork(exec);
	if (ft_is_builtin_new(parse->cmd[0]) && exec->pid == 0)
	{
		close(exec->pipes[1]);
		close(exec->pipes[0]);
		ft_child_for_sys(parse, envp, env_head);
	}
	else if (!ft_is_builtin_new(parse->cmd[0]) && exec->pid == 0)
	{
		close(exec->pipes[1]);
		close(exec->pipes[0]);
		ft_child_for_built(parse, env_head, EX);
	}
	else
	{
		close(exec->pipes[1]);
		ft_parent(exec);
	}
}

void	ft_write_to_pipe(t_exec *exec)
{
	dup2(exec->pipes[1], STDOUT_FILENO);
	close(exec->pipes[1]);
}

int	ft_choose_outfile(t_exec *exec, t_parse *parse)
{
	while (parse != NULL)
	{
		if (parse->op == OUT)
		{
			exec->outfile = open(parse->cmd[0], O_RDWR | O_CREAT | O_TRUNC, 0777);
			close(exec->pipes[1]);
		}
		if (parse->op == RIGHT)
		{
			exec->outfile = open(parse->cmd[0], O_RDWR | O_CREAT | O_APPEND, 0777);
			close(exec->pipes[1]);
		}
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

int	ft_file_only(t_parse *parse, t_exec *exec)
{
	while (parse != NULL)
	{
		if (parse->op == IN || parse->op == LEFT)
		{
			if (parse->op == IN)
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
					return 1;
				}
				if (parse->next->op != IN && parse->next->op != LEFT)
				{
					close(exec->temp_fd);
					dup2(exec->infile, exec->temp_fd);
				}
				close(exec->infile);
			}
			else if (parse->op == LEFT)
			{
				close(exec->temp_fd);
				ft_heredoc(exec, parse);
			}
		}
		else
		{
			// ft_in_is_tempfd(exec);
			ft_choose_outfile(exec, parse);
		}
		parse = parse->next;
	}
	return 0;
}

void	ft_execution(t_parse *parse, char **envp, t_env_list **env_head)
{
	t_exec	exec;
	int		ret;
	int		out_action;

	out_action = 0;
	ft_init_exec(&exec, parse);
	if (!parse)
		return ;


	if (exec.cmdcount == 0) // added later
	{
		ft_file_only(parse, &exec); // added later
		return ;
	}


	while (parse != NULL)
	{
		ret = ft_redirect_in(&exec, &parse);
		if (ret == -1)
			return ;
		if (ret == 0)
		{
			ft_pipe(&exec);
			ft_in_is_tempfd(&exec);



			if (parse->next != NULL)
			{
				if (parse->next->op == PIPE || parse->next->pipe_flag == PIPE)
				{
					ft_write_to_pipe(&exec);
				}
				if (parse->next->op == OUT || parse->next->op == RIGHT)
				{
					out_action = ft_choose_outfile(&exec, parse);
				}
			}
			// else if (exec.cmdcount == 0 && parse->op >= 2 && parse->op <= 5) // added later 
			// {
			// 	out_action = ft_choose_outfile(&exec, parse);
			// }
			else
			{
				dup2(exec.stout, STDOUT_FILENO);
				close(exec.stout);
			}


			if (exec.cmdcount == 1 && !ft_is_builtin_new(parse->cmd[0]))
			{
				ft_child_for_built(parse, env_head, RET);
				ft_parent(&exec);
			}
			else if (parse->op == CMD || parse->op == PIPE)
				ft_exec_multiple(parse, envp, env_head, &exec);
			else
				ft_parent(&exec);


			if (out_action == 1)
				break ;
			if (out_action == 2)
			{
				while (parse->next->op == OUT || parse->next->op == RIGHT)
					parse = parse->next;
				out_action = 0;
			}
		}
		parse = parse->next;
	}
	ft_wait(exec);
	ft_close_all(&exec);
}
