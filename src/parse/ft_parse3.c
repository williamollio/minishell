#include "../../includes/minishell.h"

void ft_cmd(int i, t_parse **parse, char **arr)
{
	if (arr[i + 1] != NULL)
	{
		if (!ft_operator((i + 1), parse, arr) &&
			!ft_arg((i + 1), parse, arr))
		{
			ft_get_last(parse)->str = arr[i + 1];
		}
	}
	else
		return ;
}
