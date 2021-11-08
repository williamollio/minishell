#include "../../includes/minishell.h"

int	ft_countrows(char **paths)
{
	int	i;

	i = 0;
	while (paths[i] != NULL)
		i++;
	return (i);
}

char	*ft_check_commandpath(int rows, char **paths, char *cmd)
{
	int		i;
	char	*ret;
	char	*slash;

	i = 0;
	while (i <= rows)
	{
		slash = ft_strjoin(paths[i], "/");
		ret = ft_strjoin(slash, cmd);
		ft_free1(slash);
		if (access(ret, F_OK) != -1)
		{
			return (ret);
		}
		i++;
	}
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2); // because if the path is not valid i return this message, william checks if the cmd exists first
	exit(0);
}

void	ft_create_split(t_sys *sys, t_parse *test)
{
	sys->join_space = ft_strjoin(test->cmd, " ");
	sys->join_arg = ft_strjoin(sys->join_space, test->arg);
	ft_free1(sys->join_space);
	sys->join_space = ft_strjoin(sys->join_arg, " ");
	ft_free1(sys->join_arg);
	sys->join_str = ft_strjoin(sys->join_space, test->str);
	ft_free1(sys->join_space);
	sys->split = ft_split(sys->join_str, ' ');
	ft_free1(sys->join_str);
}

void	ft_child_for_sys(t_parse *test, char **envp, t_env_list **env_head)
{
	t_sys	sys;

	ft_create_split(&sys, test);
	sys.rowsinpath = 0;
	sys.pathname = ft_extract_content(*env_head, "PATH");
	if (sys.pathname != NULL)
	{
		sys.paths = ft_split(sys.pathname, ':');
		ft_free1(sys.pathname);
		sys.rowsinpath = ft_countrows(sys.paths);
		sys.cmdpath = ft_check_commandpath(sys.rowsinpath, sys.paths, test->cmd);
		ft_free2(sys.paths);
		if (execve(sys.cmdpath, sys.split, envp) == -1)
		{
			ft_free2(sys.split);
			ft_free1(sys.cmdpath);
			perror("execve failed\n");
			exit(0);
		}
	}
	else
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(test->cmd, 2);
		ft_putendl_fd(": No such file or directory", 2);
		ft_free2(sys.split);
		exit(0);
	}
}
