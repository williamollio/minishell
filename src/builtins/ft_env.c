#include "../../includes/minishell.h"

// no loeaks
void	ft_env(t_env_list *env_head)
{
	char	*path_existence;

	path_existence = ft_extract_content(env_head, "PATH");
	if (path_existence == NULL)
	{
		exit_status = 127;
		ft_putendl_fd("bash: env: No such file or directory", 2);
	}
	else
	{
		exit_status = 0;
		ft_print_list(env_head);
	}
	free(path_existence);
}
