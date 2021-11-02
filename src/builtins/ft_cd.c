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

char	*ft_extract_content(t_env_list *env_head, char *var)
{
	char	*content;
	int		x;

	while (ft_strncmp(env_head->var, var, ft_strlen(env_head->var)) != 0)
	{
		env_head = env_head->next;
		if (env_head == NULL)
			return (NULL);
	}
	x = 0;
	while (env_head->full[x] != '=')
	x++;
	content = ft_substr(env_head->full, x + 1, ft_strlen(env_head->full) - x);
	return (content);
}


void	ft_reset_paths(t_env_list **env_head, char *current, char *old)
{
	ft_change_env_var(env_head, "PWD", current);
	ft_change_env_var(env_head, "OLDPWD", old);
}

// make sure that william parses - as string and not as arg for cd
void	ft_cd(t_env_list **env_head, char *path)
{
	char	*old;
	char	*current;
	char	*home;
	
	old = ft_extract_content(*env_head, "OLDPWD");
	current = ft_extract_content(*env_head, "PWD");
	home = ft_extract_content(*env_head, "HOME");
	if (path[0] == '\0' || ((ft_strncmp(path, "--", 2) == 0 && ft_strlen(path) == 2)) || (ft_strncmp(path, "~", 1) == 0 && ft_strlen(path) == 1)) // fuer den fall cd ohne path oder cd --
	{
		if (home == NULL)
			return ;
		ft_change_env_var(env_head, "OLDPWD", getcwd(NULL, MAXPATHLEN));
		if (chdir(home) == -1)
		{
			perror("");
			ft_reset_paths(env_head, current, old);
		}
		ft_change_env_var(env_head, "PWD", getcwd(NULL, MAXPATHLEN));
	}
	else if (ft_strncmp(path, "-", 1) == 0 && ft_strlen(path) == 1)
	{
		if (old == NULL)
			return ;
		ft_change_env_var(env_head, "OLDPWD", getcwd(NULL, MAXPATHLEN));
		if (chdir(old) == -1)
		{
			perror("");
			ft_reset_paths(env_head, current, old);
		}
		else
			printf("%s\n", old);
		ft_change_env_var(env_head, "PWD", getcwd(NULL, MAXPATHLEN));
	}
	else if (ft_strncmp(path, "~-", 2) == 0 && ft_strlen(path) == 2)
	{
		if (old == NULL)
			return ;
		ft_change_env_var(env_head, "OLDPWD", getcwd(NULL, MAXPATHLEN));
		if (chdir(old) == -1)
		{
			perror("");
			ft_reset_paths(env_head, current, old);
		}
		ft_change_env_var(env_head, "PWD", getcwd(NULL, MAXPATHLEN));
	}
	else
	{
		ft_change_env_var(env_head, "OLDPWD", getcwd(NULL, MAXPATHLEN));
		if (chdir(path) == -1)
		{
			perror(path);
			ft_reset_paths(env_head, current, old);
		}
		ft_change_env_var(env_head, "PWD", getcwd(NULL, MAXPATHLEN));
	}
	// ft_free1(old);
	// ft_free1(current); //double free somewhere
	// ft_free1(home);
	return ;
}