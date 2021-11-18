#include "../../includes/minishell.h"

int	ft_check_for_n(char *str)
{
	int	i;

	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_echo_dash_n(char **cmd, int printflag, int i)
{
	i++;
	while (cmd[i])
	{
		if (ft_strncmp(cmd[i], "-n", 2) != 0)
		{
			if (printflag != 0)
				write(1, " ", 1);
			ft_putstr_fd(cmd[i], 1);
			printflag++;
		}
		else if (ft_strncmp(cmd[i], "-n", 2) == 0 && ft_check_for_n(cmd[i]))
		{
			if (printflag != 0)
				write(1, " ", 1);
			ft_putstr_fd(cmd[i], 1);
			printflag++;
		}
		i++;
	}
}

void	ft_echo(char **cmd)
{
	int	i;
	int	printflag;

	printflag = 0;
	i = 1;
	exit_status = 0;
	if (!cmd[1])
		write(1, "\n", 1);
	else if (ft_strncmp(cmd[1], "-n", 2) == 0 && !ft_check_for_n(cmd[1]))
		ft_echo_dash_n(cmd, printflag, i);
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
