#include "../../includes/minishell.h"

void	ft_change_env_var(t_env **env_head, char *change, char *new)
{
	t_env	*temp;
	char	*equal_temp;

	temp = *env_head;
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

void	ft_cd_go_back(t_env **env_head, char *old, char *current, int pr)
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
		ft_reset_paths(env_head, current, old);
		return ;
	}
	else
	{
		if (pr == 1)
			ft_putendl_fd(old, 1);
		ft_free_current_old(&current, &old);
	}
	ft_change_env_var(env_head, "PWD", getcwd(NULL, MAXPATHLEN));
}

void	ft_cd_go_home(t_env **env_head, char *old, char *current)
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
		ft_reset_paths(env_head, current, old);
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

void	ft_cd(t_env **env_head, char *p)
{
	t_cd	cd;

	ft_init_cd(&cd, env_head);
	if (p == NULL || ((ft_strncmp(p, "--", 2) == 0 && ft_strlen(p) == 2))
		|| (ft_strncmp(p, "~", 1) == 0 && ft_strlen(p) == 1))
		ft_cd_go_home(env_head, cd.old, cd.current);
	else if (ft_strncmp(p, "-", 1) == 0 && ft_strlen(p) == 1)
		ft_cd_go_back(env_head, cd.old, cd.current, 1);
	else if (ft_strncmp(p, "~-", 2) == 0 && ft_strlen(p) == 2)
		ft_cd_go_back(env_head, cd.old, cd.current, 0);
	else
	{
		ft_change_env_var(env_head, "OLDPWD", getcwd(NULL, MAXPATHLEN));
		if (chdir(p) == -1)
		{
			perror(p);
			exit_status = 1;
			ft_reset_paths(env_head, cd.current, cd.old);
			return ;
		}
		else
			ft_free_current_old(&cd.current, &cd.old);
		ft_change_env_var(env_head, "PWD", getcwd(NULL, MAXPATHLEN));
	}
	return ;
}
