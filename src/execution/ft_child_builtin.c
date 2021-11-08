#include "../../includes/minishell.h"

void	ft_child_for_built(t_parse *test, t_env_list **env_head, int status)
{
	if (ft_strncmp(test->cmd, "echo", 4) == 0)
		ft_echo(test->str, test->arg);
	else if (ft_strncmp(test->cmd, "export", 6) == 0)
		ft_export_node(env_head, test->str);
	else if (ft_strncmp(test->cmd, "unset", 5) == 0)
		ft_unset_node(env_head, test->str);
	else if (ft_strncmp(test->cmd, "env", 3) == 0)
		ft_env(*env_head);
	else if (ft_strncmp(test->cmd, "exit", 4) == 0)
		ft_exit();
	else if (ft_strncmp(test->cmd, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(test->cmd, "cd", 2) == 0)
		ft_cd(env_head, test->str);
	if (status == EX)
		exit(0);
	else if (status == RET)
		return ;
}
