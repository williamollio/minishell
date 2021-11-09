#include "../../includes/minishell.h"

void	ft_pwd(void)
{
	char	*pwd;

	exit_status = 0;
	pwd = getcwd(NULL, FILENAME_MAX);
	printf("%s\n", pwd);
	free(pwd);
}
