#include "../../includes/minishell.h"

void	ft_child_for_built(t_parse *parse, t_env_list **env_head, int status)
{
	if (ft_strncmp(parse->cmd, "echo", 4) == 0)
		ft_echo(parse->str, parse->arg);
	else if (ft_strncmp(parse->cmd, "export", 6) == 0)
		ft_export_node(env_head, parse->str);
	else if (ft_strncmp(parse->cmd, "unset", 5) == 0)
		ft_unset_node(env_head, parse->str);
	else if (ft_strncmp(parse->cmd, "env", 3) == 0)
		ft_env(*env_head);
	else if (ft_strncmp(parse->cmd, "exit", 4) == 0)
		ft_exit(parse);
	else if (ft_strncmp(parse->cmd, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(parse->cmd, "cd", 2) == 0)
		ft_cd(env_head, parse->str);
	if (status == EX)
		exit(exit_status);
	else if (status == RET)
		return ;
}
