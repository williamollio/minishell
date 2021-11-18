#include "../../includes/minishell.h"

void	ft_error(char *line)
{
	printf("zsh: command not found : %s\n", line);
}
