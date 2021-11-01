#include "../../includes/minishell.h"

int ft_first(char **paths, int i, t_parse **parse, char **arr)
{
	(void)parse;
	if (ft_operator_tool(i, arr) == 1)
	{
		ft_msg_pars(arr[0]);
		return (1);
	}
	if (!ft_is_builtin(arr[0]) &&
		!check_commandpath(paths, arr[0]) &&
		!ft_operator_tool(i, arr))
	{
		ft_msg_cmd(arr[0]);
		return (1);
	}
	return (0);
}

int ft_pipe_error(int i, t_parse **parse, char **arr, int op)
{
	char	**paths;
	(void)parse;
	paths = ft_get_paths(NULL);
	if (op == 1 &&
		!check_commandpath(paths, arr[i + 1]) &&
		!ft_is_builtin(arr[i + 1]))
	{
		ft_msg_cmd(arr[i + 1]);
		return (1);
	}
	else
		return (0);

}

void ft_msg_cmd(char *arr)
{
	char	*message;

	message = ": command not found\n";
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(arr, 2);
	ft_putstr_fd(message, 2);
}

void ft_msg_pars(char *arr)
{

	char	*message;

	message = "parse error near `";
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(arr, 2);
	ft_putstr_fd("'\n", 2);
}

void ft_error(char *line)
{
	printf("zsh: command not found : %s\n", line);
}