#include "../../includes/minishell.h"

// int ft_str(int i, t_parse **parse, char **arr)
// {
// 	t_parse *last;

// 	if (*parse != NULL)
// 		last = ft_get_last(parse);
// 	else
// 		return (0);
// 	if (arr[i + 1] != NULL && !ft_operator_tool((i + 1), arr))
// 		last->str = arr[i + 1];
// 	else
// 		return (0);
// 	return (1);
// }

void ft_append(int i, char **arr, char **str)
{
	char	*temp;

	if (ft_strncmp(*str, "", 1) == 0)
		*str = arr[i];
	else
	{
		temp = ft_strjoin(*str, " ");
		ft_free1(*str);
		*str = temp;
		temp = ft_strjoin(*str, arr[i]);
		ft_free1(*str);
		*str = temp;
	}
}
void ft_arg(int *x, t_parse **parse, char **arr)
{
	t_parse	*last;
	int		i;

	i = *x;
	if (*parse != NULL)
		last = ft_get_last(parse);
	else
		return ;
	if (last->cmd)
	{
		while (arr[*x] != '\0' && arr[*x][0] == '-' && !ft_operator_tool(*x, arr))
		{
			ft_append(*x, arr, &last->arg);
			*x += 1;
		}
		while (arr[*x] != '\0' && !ft_operator_tool(*x, arr))
		{
			ft_append(*x, arr, &last->str);
			*x += 1;
		}
	}
	return ;
}

// void ft_cmd(int *x, t_parse **parse, char **arr)
// {
// 	int	i;
// 	int	i1;

// 	i = *x;
// 	i1 = i + 1;
// 	if (arr[i] != NULL && arr[i1] != NULL)
// 	{
// 		while (!ft_operator_tool(i1, arr) &&
// 			arr[i1][0] != '-')
// 		{
// 			ft_get_last(parse)->str = arr[i1];
// 			*x += 1;
// 		}
// 	}
// 	else
// 		return ;
// }
