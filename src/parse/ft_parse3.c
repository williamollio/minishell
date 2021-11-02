#include "../../includes/minishell.h"

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
	if (last->cmd && ft_strncmp(last->str, "", 1) == 0)
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
