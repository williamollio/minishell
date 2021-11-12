#include "../../includes/minishell.h"

// checks for dumb shit like this export = or export =====
// also checks shit like this export test
int	ft_export_edgecase(char *str)
{
	char		*err;
	char		*var;
	
	if (str[0] == '=')
	{
		err = ft_substr(str, 0, ft_strlen(str));
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(err, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		free(err);
		exit_status = 1;
		return (1);
	}
	if (!ft_strchr(str, '='))
		return (1);
	var = ft_get_var(str);
	if (ft_strncmp(var, "_", ft_strlen(var)) == 0)
	{
		free(var);
		return (1);
	}
	if (!ft_isalpha(var[0]) &&  var[0] != '_')
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		free(var);
		exit_status = 1;
		return (1);
	}
	free(var);
	return (0);
}

// in here i write a new var to env and override the content if var already exists
void	ft_add_export(t_env_list **env_head, char *str)
{
	t_env_list	*temp;
	t_env_list	*prev;
	t_env_list	*temp_2;
	t_env_list	*newNode;

	temp = *env_head;
	prev = *env_head;
	if (ft_export_edgecase(str) == 1)
		return ;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->var, ft_get_var(str), ft_strlen(temp->var)) == 0 && ft_strlen(temp->var) == ft_strlen(ft_get_var(str)))
		{
			free(temp->content);
			temp->content = ft_get_content(str); // gets allocated
			free(temp->full);
			temp->full = ft_strdup(str); // i dont know if william allocates this string before passing it to me
			free(temp->var);
			temp->var = ft_get_var(str); // gets allocated
			return ;
		}	
		if (ft_strncmp(temp->var, "_", ft_strlen(temp->var)) == 0)
			break ;
		prev = temp;
		temp = temp->next;
	}
	temp = prev;
	temp_2 = temp->next;
	newNode = malloc(sizeof(t_env_list));
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

void	ft_sort_env(t_env_list *env_head)
{
	t_env_list	*sorted;

	while (env_head != NULL)
	{
		ft_addorder(&sorted, env_head->full);
		env_head = env_head->next;
	}
	ft_print_list(sorted);
	ft_free_list(&sorted);
	return ;
}

// checks if there is multiple things to export
void	ft_export_node(t_env_list **env_head, char **cmd)
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
