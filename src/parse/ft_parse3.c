#include "../../includes/minishell.h"

// static void ft_append(int i, char **arr, char **str)
// {
// 	char	*temp;

// 	if (ft_strncmp(*str, "", 1) == 0)
// 		*str = arr[i];
// 	else
// 	{
// 		temp = ft_strjoin(*str, " ");
// 		ft_free1(*str);
// 		*str = temp;
// 		temp = ft_strjoin(*str, arr[i]);
// 		ft_free1(*str);
// 		*str = temp;
// 	}
// }
// int ft_arg_built_in(t_parse **parse)
// {
// 	t_parse	*tmp;

// 	tmp = *parse;
// 	while (tmp != NULL)
// 	{
// 		if (tmp->flag == 6 && ft_strncmp(tmp->arg, "", 1) != 0)
// 		{
// 			if ((ft_strncmp(tmp->cmd, "echo", 4) == 0 && ft_strlen(tmp->cmd) == 4) &&
// 				(ft_strncmp(tmp->arg, "-n", 2) == 0 && ft_strlen(tmp->arg) == 2))
// 				break;
// 			else
// 			{
// 				ft_msg_arg(tmp->arg);
// 				return (EXIT_FAILURE);
// 			}
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (EXIT_SUCCESS);
// }

// int ft_arg(int *x, t_parse **parse, char **arr)
// {
// 	t_parse	*last;
// 	int		i;

// 	i = *x;
// 	if (*parse != NULL)
// 		last = ft_get_last(parse);
// 	else
// 		return (EXIT_SUCCESS);
// 	if (last->cmd && ft_strncmp(last->str, "", 1) == 0)
// 	{
// 		while (arr[*x] != '\0' && arr[*x][0] == '-' && !ft_operator_tool(*x, arr))
// 		{
// 			ft_append(*x, arr, &last->arg);
// 			*x += 1;
// 		}
// 		while (arr[*x] != '\0' && !ft_operator_tool(*x, arr))
// 		{
// 			ft_append(*x, arr, &last->str);
// 			*x += 1;
// 		}
// 	}
// 	if (ft_arg_built_in(parse))
// 		return (EXIT_FAILURE);
// 	return (EXIT_SUCCESS);
// }
