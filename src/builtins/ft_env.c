#include "../../includes/minishell.h"

void	ft_env(t_env *env_head)
{
	char	*path_existence;

	path_existence = ft_extract_content(env_head, "PATH");
	if (path_existence == NULL)
	{
		g_exit_status = 127;
		ft_putendl_fd("bash: env: No such file or directory", 2);
	}
	else
	{
		g_exit_status = 0;
		ft_print_list(env_head);
	}
	free(path_existence);
}
