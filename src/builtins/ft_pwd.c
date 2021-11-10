#include "../../includes/minishell.h"

void	ft_pwd(void)
{
	char	*pwd;

	exit_status = 0;
	pwd = getcwd(NULL, FILENAME_MAX);
	ft_putendl_fd(pwd, 1);
	free(pwd);
}
