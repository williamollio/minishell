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

// pwd should maybe not change when cd fails
void	ft_cd(t_env_list **env_head, char *str)
{
	char	*path;
	
	path = ft_substr(str, 3, ft_strlen(str) - 3);
	printf("path = %s\n", path);
	//usually str is already pased in if i calll it in childe for builtin beacuse of parsing
	if (path[0] == '\0' || (ft_strncmp(path, "--", 2) == 0 && ft_strlen(path) == 2) || (ft_strncmp(path, "~", 1) == 0 && ft_strlen(path) == 1)) // fuer den fall cd ohne path oder cd --
	{
		ft_change_env_var(env_head, "OLDPWD", getcwd(NULL, FILENAME_MAX));
		if (chdir(getenv("HOME")) == -1)
			perror("");
		ft_change_env_var(env_head, "PWD", getcwd(NULL, FILENAME_MAX));
		return ;
	}
	else if (ft_strncmp(path, "-", 1) && ft_strlen(path) == 1)
	{
		// if (lastcd == NULL)
		// 	return ;
		// else
		// {
		// 	if (chdir(*lastcd) == -1)
		// 		perror(*cd);
		// } 
	}
	else
	{
		ft_change_env_var(env_head, "OLDPWD", getcwd(NULL, FILENAME_MAX));
		if (chdir(path) == -1)
			perror(path);
		ft_change_env_var(env_head, "PWD", getcwd(NULL, FILENAME_MAX));
		return ;
	}
}