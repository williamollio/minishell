#include "../../includes/minishell.h"

// already worked on this
// no leaks
void	ft_echo(char **cmd)
{
	int	i;

	i = 1;
	if (!cmd[1])
		write(1, "\n", 1);
	else if (ft_strncmp(cmd[1], "-n", 2) == 0 && ft_strlen(cmd[1]) == 2)
	{
		i++;
		while (cmd[i])
		{
			ft_putstr_fd(cmd[i], 1);
			write(1, " ", 1);
			i++;
		}
	}
	else
	{
		while (cmd[i + 1])
		{
			ft_putstr_fd(cmd[i], 1);
			write(1, " ", 1);
			i++;
		}
		ft_putendl_fd(cmd[i], 1);
	}
}
