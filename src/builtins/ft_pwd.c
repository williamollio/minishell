#include "../../includes/minishell.h"

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, FILENAME_MAX);
	printf("%s\n", pwd);
	free(pwd);
}
