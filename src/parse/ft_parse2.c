#include "../../includes/minishell.h"

void ft_file(int i, t_parse **parse, char **arr, int op)
{
	if (op >= 2 && op <= 5)
	{
		ft_addback_parse(parse, arr[i + 1], FILE);
		ft_get_last(parse)->op = op;
	}
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

	if (arr[i] == NULL || arr[i + 1] == NULL)
		return(EXIT_SUCCESS);
	op = ft_operator_tool(i, arr);
	if ((* parse) != NULL && op != 0)
		ft_get_last(parse)->op = op;
	if (ft_pipe_error(i, parse, arr, op))
		return (EXIT_FAILURE);
	ft_file(i, parse, arr, op);
	printf("arr[i%d] %s\n",i, arr[i]);
	printf("last->str : %s\n", ft_get_last(parse)->str);
	return (EXIT_SUCCESS);
}

