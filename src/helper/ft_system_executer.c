// #include "../../includes/minishell.h"

// char	*ft_check_commandpath_2(int rows, char **paths, char *cmd)
// {
// 	int		i;
// 	char	*ret;
// 	char	*slash;

// 	i = 0;
// 	while (i <= rows)
// 	{
// 		slash = ft_strjoin(paths[i], "/");
// 		ret = ft_strjoin(slash, cmd);
// 		ft_free1(slash);
// 		if (access(ret, F_OK) != -1)
// 		{
// 			return (ret);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

// void	ft_system_executer(char *str, char **envp)
// {
// 	pid_t	childpid;
// 	char	**cmd;
// 	char	*cmdpath;
// 	char	**paths;
// 	char	*path;
// 	int		rows;

// 	cmd = ft_split(str, ' ');
// 	path = getenv("PATH");
// 	paths = ft_split(path, ':');
// 	rows = ft_countrows(paths);
// 	cmdpath = ft_check_commandpath_2(rows, paths, cmd[0]);
// 	ft_free2(paths);
// 	if (cmdpath == NULL)
// 	{
// 		ft_free2(cmd);
// 		return ;
// 	}
// 	childpid = fork();
// 	if (childpid == -1)
// 	{
// 		perror("fork");
// 		ft_free2(cmd);
// 		ft_free1(cmdpath);
// 		return ;
// 	}
// 	if (childpid == 0)
// 		execve(cmdpath, cmd, envp);
// 	else
// 	{
// 		wait(NULL);
// 		ft_free2(cmd);
// 		ft_free1(cmdpath);
// 		return ;
// 	}
// }
