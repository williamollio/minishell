#include "../../includes/minishell.h"

void	ft_env(t_env_list *env_head)
{
	if (ft_extract_content(env_head, "PATH") == NULL)
		ft_putendl_fd("bash: env: No such file or directory", 2);
	else
		ft_print_list(env_head);
}
