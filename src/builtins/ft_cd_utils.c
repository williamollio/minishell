#include "../../includes/minishell.h"

void	ft_reset_paths(t_env  **env_head, char *current, char *old)
{
	ft_change_env_var(env_head, "PWD", current);
	ft_change_env_var(env_head, "OLDPWD", old);
}

void	ft_free_current_old(char **current, char **old)
{
	if (*current != NULL)
		free(*current);
	if (*old != NULL)
		free(*old);
}

void	ft_init_cd(t_cd *cd, t_env **env_head)
{
	exit_status = 0;
	cd->old = ft_extract_content(*env_head, "OLDPWD");
	cd->current = ft_extract_content(*env_head, "PWD");
}
