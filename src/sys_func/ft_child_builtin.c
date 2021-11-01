#include "../../includes/minishell.h"

//compare with ft_builtin in minishell.c
//echo is improvised
void	ft_child_for_built(t_parse *test, t_env_list **env_head)
{
	// add -n flag
	if (ft_strncmp(test->cmd, "echo", 4) == 0)
	{
		// ft_echo(line);
		printf("%s\n", test->str);
		return ;
	}
	else if (ft_strncmp(test->cmd, "export", 6) == 0)
	{
		ft_export_node(env_head, test->str);
		return ;
	}
	else if (ft_strncmp(test->cmd, "unset", 5) == 0)
	{
		ft_unset_node(env_head, test->str);
		return ;
	}
	else if (ft_strncmp(test->cmd, "env", 3) == 0)
	{
		ft_print_list(*env_head);
		return ;
	}
	else if (ft_strncmp(test->cmd, "exit", 4) == 0)
		ft_exit();
	// else if (ft_strncmp(line, "cd", 2))
	// 	ft_cd(line);
	// else if (ft_strncmp(line, "pwd", 3))
	// 	ft_pwd(line);
}
