#include "../../includes/minishell.h"

int ft_str(int i, t_parse **parse, char **arr)
{
	t_parse *last;

	if (*parse != NULL)
		last = ft_get_last(parse);
	else
		return (0);
	if (arr[i + 1] != NULL && !ft_operator_tool((i + 1), arr))
		last->str = arr[i + 1];
	else
		return (0);
	return (1);
}

int ft_arg(int *x, t_parse **parse, char **arr)
{
	t_parse *last;
	int	i;

	i = *x;
	if (*parse != NULL)
		last = ft_get_last(parse);
	else
		return (0);
	if (last->cmd && arr[i][0] == '-')
		{
			last->arg = arr[i];
			if (ft_str(i, parse, arr))
				*x += 1;
		}
	else
		return (0);
	return (1);
}

void ft_cmd(int *x, t_parse **parse, char **arr)
{
	int	i;
	int	i1;

	i = *x;
	i1 = i + 1;
	if (arr[i] != NULL && arr[i + 1] != NULL)
	{
		if (!ft_operator_tool(i1, arr) &&
			!ft_arg(&i1, parse, arr))
		{
			ft_get_last(parse)->str = arr[i + 1];
			*x += 1;
		}
	}
	else
		return ;
}
