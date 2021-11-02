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
		env_head = env_head->next;
	x = 0;
	while (env_head->full[x] != '=')
	x++;
	content = ft_substr(env_head->full, x + 1, ft_strlen(env_head->full) - x);
	return (content);
}

// pwd should maybe not change when cd fails
void	ft_cd(t_env_list **env_head, char *path)
{
	char	*old;

	printf("path = %s\n", path);
	old = ft_extract_content(*env_head, "OLDPWD");
	if (path[0] == '\0' || ((ft_strncmp(path, "--", 2) == 0 && ft_strlen(path) == 2)) || (ft_strncmp(path, "~", 1) == 0 && ft_strlen(path) == 1)) // fuer den fall cd ohne path oder cd --
	{
		ft_change_env_var(env_head, "OLDPWD", getcwd(NULL, FILENAME_MAX));
		if (chdir(ft_extract_content(*env_head, "HOME")) == -1)
			perror("");
		ft_change_env_var(env_head, "PWD", getcwd(NULL, FILENAME_MAX));
		return ;
	}
	else if (ft_strncmp(path, "-", 1) == 0 && ft_strlen(path) == 1)
	{
		ft_change_env_var(env_head, "OLDPWD", getcwd(NULL, FILENAME_MAX));
		printf("%s\n", old);
		if (chdir(old) == -1)
			perror("");
		ft_change_env_var(env_head, "PWD", getcwd(NULL, FILENAME_MAX));
		return ;
	}
	else if (ft_strncmp(path, "~-", 2) == 0 && ft_strlen(path) == 2)
	{
		ft_change_env_var(env_head, "OLDPWD", getcwd(NULL, FILENAME_MAX));
		if (chdir(old) == -1)
			perror("");
		ft_change_env_var(env_head, "PWD", getcwd(NULL, FILENAME_MAX));
		return ;
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