#include "../../includes/minishell.h"

void	ft_identifier_error(char *err, char *var)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(err, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	free(var);
	exit_status = 1;
}

// checks for dumb shit like this export = or export =====
// also checks shit like this export test
int	ft_export_edgecase(char *str)
{
	char		*var;
	int			i;

	i = 0;
	if (!ft_strchr(str, '='))
		return (1);
	var = ft_get_var(str);
	if (str[0] == '=')
	{
		ft_identifier_error(str, var);
		return (1);
	}
	while (var[i])
	{
		if (var[i] == '-')
		{
			ft_identifier_error(str, var);
			return (1);
		}
		i++;
	}
	if (ft_strncmp(var, "_", ft_strlen(var)) == 0)
	{
		free(var);
		return (1);
	}
	if (!ft_isalpha(var[0]) &&  var[0] != '_')
	{
		ft_identifier_error(str, var);
		return (1);
	}
	free(var);
	return (0);
}

// in here i write a new var to env and override the content if var already exists
void	ft_add_export(t_env **env_head, char *str)
{
	t_env	*temp;
	t_env	*prev;
	t_env	*temp_2;
	t_env	*newNode;
	char		*str_var;

	temp = *env_head;
	prev = *env_head;
	if (ft_export_edgecase(str) == 1)
		return ;
	str_var = ft_get_var(str);
	while (temp != NULL)
	{
		if (ft_strncmp(temp->var, str_var, ft_strlen(temp->var)) == 0 && ft_strlen(temp->var) == ft_strlen(str_var))
		{
			free(temp->content);
			temp->content = ft_get_content(str); // gets allocated
			free(temp->full);
			temp->full = ft_strdup(str); // i dont know if william allocates this string before passing it to me
			free(temp->var);
			temp->var = ft_get_var(str); // gets allocated
			free(str_var);
			return ;
		}
		if (ft_strncmp(temp->var, "_", ft_strlen(temp->var)) == 0)
			break ;
		prev = temp;
		temp = temp->next;
	}
	free(str_var);
	temp = prev;
	temp_2 = temp->next;
	newNode = malloc(sizeof(t_env));
	newNode->full = ft_strdup(str); // same problem: does william allocate it?
	newNode->var = ft_get_var(str); // gets allocated
	newNode->content = ft_get_content(str); // gets allocated
	temp->next = newNode;
	newNode->next = temp_2;
	if (*env_head == NULL)
	{
		*env_head = newNode;
		return ;
	}
}

void	ft_sort_env(t_env *env_head)
{
	t_env	*sorted;

	sorted = NULL;
	while (env_head != NULL)
	{
		ft_addorder(&sorted, env_head->full);
		env_head = env_head->next;
	}
	ft_print_list(sorted);
	ft_free_list(&sorted);
	return ;
}

void	ft_export_node(t_env **env_head, char **cmd)
{
	int		i;

	exit_status = 0;
	if (cmd[1] == NULL)
	{
		ft_sort_env(*env_head);
		return ;
	}
	i = 1;
	while(cmd[i])
	{
		ft_add_export(env_head, cmd[i]);
		i++;
	}
	return ;
}
