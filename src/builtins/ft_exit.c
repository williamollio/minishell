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

void	ft_check_exit_string(t_parse *test, char *str)
{
	int	i;
	int	num;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_putstr_fd("bash: exit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putendl_fd(": numeric argument required", 2);
			ft_free_list_parse(&test);
			exit(255);
		}
		i++;
	}
	num = ft_atoi(str); // should be atoll here
	if (num > 255 || num < 0)
		exit_status = ft_calculate_exit_status(num);
	else
		exit_status = num;
	ft_free_list_parse(&test);
	exit(exit_status);
}

void	ft_exit(t_parse *test)
{
	if (test->arg[0] == '\0' && test->str[0] == '\0')
	{
		ft_free_list_parse(&test); // need to check if it works if i  exit ina child or in a shell inside of a shell
		exit(0);
	}
	else if (test->arg[0] != '\0' && test->str[0] != '\0')
	{
		ft_putendl_fd("bash: exit: too many arguments", 2);
		exit_status = 1;
		return ;
	}
	else if (test->arg[0] == '\0' && test->str[0] != '\0')
		ft_check_exit_string(test, test->str);
	else
		ft_check_exit_string(test, test->arg);
}
