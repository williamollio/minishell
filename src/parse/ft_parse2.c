#include "../../includes/minishell.h"

void ft_file(int i, t_parse **parse, char **arr, int op)
{
	if (op >= 2 && op <= 5)
		ft_addback_parse(parse, arr[i + 1], FILE);
}

int ft_operator_tool(int i, char **arr)
{
	if (ft_strchr(arr[i], '|') != NULL)
		return (1);
	else if (ft_strnstr(arr[i], "<<", 2) != NULL)
		return (4);
	else if (ft_strnstr(arr[i], ">>", 2) != NULL)
		return (5);
	else if (ft_strchr(arr[i], '>') != NULL)
		return (2);
	else if (ft_strchr(arr[i], '<') != NULL)
		return (3);
	else
		return (0);
}

int ft_operator(int i, t_parse **parse, char **arr)
{
	int	op;

	op = ft_operator_tool(i, arr);
	ft_file(i, parse, arr, op);
	if (op != 0)
		ft_get_last(parse)->op = op;
	else
		return (0);
	return (1);
}

int ft_arg(int i, t_parse **parse, char **arr)
{
	t_parse *last;

	last = ft_get_last(parse);
	if (last->cmd &&
		arr[i][0] == '-')
		last->arg = arr[i];
	else
		return (0);
	return (1);
}

void ft_first(char **paths, int i, t_parse **parse, char **arr)
{
	char *message;

	message = "command not found : ";
	if (!ft_is_builtin(arr[0]) &&
		!check_commandpath(paths, arr[0]) &&
		!ft_operator(i, parse, arr))
	{
		ft_putstr_fd("minishell : ", 2);
		ft_putstr_fd(message, 2);
		ft_putstr_fd(arr[0], 2);
		ft_putstr_fd("\n", 2);
		exit(EXIT_FAILURE);
	}
}
