#include "../../includes/minishell.h"

void	ft_child_for_built(t_parse *parse, t_env_list **env_head, int status)
{
	if (ft_strncmp(parse->cmd[0], "echo", 4) == 0)
		ft_echo(parse->cmd); // no leaks
	else if (ft_strncmp(parse->cmd[0], "export", 6) == 0)
		ft_export_node(env_head, parse->cmd); // no leaks
	else if (ft_strncmp(parse->cmd[0], "unset", 5) == 0)
		ft_unset_node(env_head, parse->cmd); // no leaks
	else if (ft_strncmp(parse->cmd[0], "env", 3) == 0)
		ft_env(*env_head); // no leaks
	else if (ft_strncmp(parse->cmd[0], "exit", 4) == 0)
		ft_exit(parse);
	else if (ft_strncmp(parse->cmd[0], "pwd", 3) == 0)
		ft_pwd(); // no leaks
	else if (ft_strncmp(parse->cmd[0], "cd", 2) == 0)
		ft_cd(env_head, parse->cmd[1]); // no leaks
	if (status == EX)
		exit(exit_status);
	else if (status == RET)
		return ;
}
