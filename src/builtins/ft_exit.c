#include "../../includes/minishell.h"

int	ft_calculate_exit_status(int num)
{
	if (num > 255)
	{
		while (num > 255)
			num -= 256;
	}
	else
	{
		while (num < 0)
			num += 256;
	}
	return (num);
}

void	ft_exit_error(char *str, t_parse *parse)
{
	ft_putendl_fd("exit", 2);
	ft_putstr_fd("bash: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": numeric argument required", 2);
	ft_free_list_parse(&parse);
	exit(255);
}

void	ft_check_exit_string(t_parse *parse, char *str)
{
	int			i;
	long long	num;

	i = 0;
	num = ft_atoll(str);
	while(str[i] == '-' || str[i] == '+')
		i++;
	if (num == 0 && str[i] != '0')
		ft_exit_error(str, parse);
	if (num > 255 || num < 0)
		exit_status = ft_calculate_exit_status(num);
	else
		exit_status = num;
	ft_free_list_parse(&parse);
	ft_putendl_fd("exit", 2);
	exit(exit_status);
}

void	ft_exit(t_parse *parse)
{
	int	x;

	x = 0;
	if (parse->cmd[1] == NULL)
	{
		ft_free_list_parse(&parse); // need to check if it works if i  exit ina child or in a shell inside of a shell
		ft_putendl_fd("exit", 2);
		exit(0);
	}
	while (parse->cmd[1][x])
	{
		if (!ft_isdigit(parse->cmd[1][x]) && parse->cmd[1][x] != '+' && parse->cmd[1][x] != '-')
			ft_exit_error(parse->cmd[1], parse);
		x++;
	}
	if (parse->cmd[2] != NULL)
	{
		ft_putendl_fd("bash: exit: too many arguments", 2);
		exit_status = 1;
		ft_putendl_fd("exit", 2);
		return ;
	}
	else
		ft_check_exit_string(parse, parse->cmd[1]);
}
