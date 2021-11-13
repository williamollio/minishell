#include "../../includes/minishell.h"

void	ft_change_env_var(t_env_list **env_head, char *change, char *new)
{
	t_env_list *temp;

	temp = *env_head;
	char	*equal_temp;
	while (ft_strncmp(temp->var, change, ft_strlen(change)) != 0)
	{
		temp = temp->next;
		if (temp == NULL)
			return ;
	}
	free(temp->content);
	temp->content = new;
	free(temp->full);
	equal_temp = ft_strjoin(temp->var, "=");
	temp->full = ft_strjoin(equal_temp, temp->content);
	free(equal_temp);
}

void	ft_reset_paths(t_env_list **env_head, char *current, char *old)
{
	ft_change_env_var(env_head, "PWD", current);
	ft_change_env_var(env_head, "OLDPWD", old);
}

void	ft_free_current_old(char **current, char **old)
{
	if (*current != NULL)
		free(*current);
	if (*old != NULL)
		free(*old);
}

void	ft_cd_go_back(t_env_list **env_head, char *old, char *current, int print)
{
	if (old == NULL)
	{
		ft_putendl_fd("bash: cd: OLDPWD not set", 2);
		exit_status = 1;
		ft_free_current_old(&current, &old);
		return ;
	}
	ft_change_env_var(env_head, "OLDPWD", getcwd(NULL, MAXPATHLEN));
	if (chdir(old) == -1)
	{
		perror(old);
		exit_status = 1;
		ft_reset_paths(env_head, current, old); // in that case i cant free current or old, beacuse their pointer get used again for the list
		return ;
	}
	else
	{
		if (print == 1)
			ft_putendl_fd(old, 1);
		ft_free_current_old(&current, &old);
	}
	ft_change_env_var(env_head, "PWD", getcwd(NULL, MAXPATHLEN));
}

void	ft_cd_go_home(t_env_list **env_head, char *old, char *current)
{
	char	*home;

	home = ft_extract_content(*env_head, "HOME");
	if (home == NULL)
	{
		ft_putendl_fd("bash: cd: HOME not set", 2);
		exit_status = 1;
		ft_free_current_old(&current, &old);
		return ;
	}
	ft_change_env_var(env_head, "OLDPWD", getcwd(NULL, MAXPATHLEN));
	if (chdir(home) == -1)
	{
		perror(home);
		exit_status = 1;
		ft_reset_paths(env_head, current, old); // in that case i cant free current or old, beacuse their pointer get used again for the list
		free(home);
		return ;
	}
	else
	{
		ft_free_current_old(&current, &old);
		free(home);
	}
	ft_change_env_var(env_head, "PWD", getcwd(NULL, MAXPATHLEN));
}

void	ft_cd(t_env_list **env_head, char *path)
{
	char	*old;
	char	*current;
	
	exit_status = 0;
	old = ft_extract_content(*env_head, "OLDPWD");
	current = ft_extract_content(*env_head, "PWD");
	if (path == NULL || ((ft_strncmp(path, "--", 2) == 0 && ft_strlen(path) == 2)) || (ft_strncmp(path, "~", 1) == 0 && ft_strlen(path) == 1))
		ft_cd_go_home(env_head, old, current);
	else if (ft_strncmp(path, "-", 1) == 0 && ft_strlen(path) == 1)
		ft_cd_go_back(env_head, old, current, 1);
	else if (ft_strncmp(path, "~-", 2) == 0 && ft_strlen(path) == 2)
		ft_cd_go_back(env_head, old, current, 0);
	else
	{
		ft_change_env_var(env_head, "OLDPWD", getcwd(NULL, MAXPATHLEN));
		if (chdir(path) == -1)
		{
			perror(path);
			exit_status = 1;
			ft_reset_paths(env_head, current, old); // in that case i cant free current or old, beacuse their pointer get used again for the list
			return ;
		}
		else
			ft_free_current_old(&current, &old);
		ft_change_env_var(env_head, "PWD", getcwd(NULL, MAXPATHLEN));
	}
	return ;
}