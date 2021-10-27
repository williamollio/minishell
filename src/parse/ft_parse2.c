#include "../../includes/minishell.h"

// void ft_file(char *str, t_parse **parse, char **arr)
// {
// 	if ()
// }

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

int	 ft_operator(int i, t_parse **parse, char **arr)
{
	//ft_file(str, parse, arr);
	int op;

	op = ft_operator_tool(i, arr);
	if (op != 0)
		ft_get_last(parse)->op = op;
	else
		return (0);
	return (1);
}