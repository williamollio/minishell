#include "../../includes/minishell.h"

void ft_append(char **last_arg, char **arg)
{
	char	*temp;

	if (ft_strncmp(*last_arg, "", 1) == 0)
		*last_arg = *arg;
	else
	{
		temp = ft_strjoin(*last_arg, " ");
		ft_free1(*last_arg);
		*last_arg = temp;
		temp = ft_strjoin(*last_arg, *arg);
		ft_free1(*last_arg);
		*last_arg = temp;
	}
}
