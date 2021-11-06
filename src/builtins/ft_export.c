#include "../../includes/minishell.h"

// chekcs for dumb shit like this export = or export =====
// also checks shit like this export test
int	ft_export_edgecase(char *str)
{
	char		*err;
	
	if (str[0] == '=')
	{
		err = ft_substr(str, 0, ft_strlen(str));
		printf("bash: export: `%s': not a valid identifier\n", err);
		free(err);
		return (1);
	}
	if (!ft_strchr(str, '='))
		return (1);
	return (0);
}

// in here i write a new var to env  over verwrite the content if var already exists
void	ft_add_export(t_env_list **env_head, char *str)
{
	t_env_list	*temp;
	t_env_list	*temp_2;
	t_env_list	*newNode;

	temp = *env_head;
	if (ft_export_edgecase(str) == 1)
		return ;
	while (ft_strncmp(temp->next->var, "_", ft_strlen(temp->next->var)))
	{
		temp = temp->next;
		if (ft_strncmp(temp->var, ft_get_var(str), ft_strlen(temp->var)) == 0 && ft_strlen(temp->var) == ft_strlen(ft_get_var(str)))
		{
			free(temp->content);
			temp->content = ft_get_content(str);
			free(temp->full); // added this so check again if export and unset works
			temp->full = str;
			free(temp->var);
			temp->var = ft_get_var(str);
			return ;
		}	
		if (temp->next == NULL) //if you deleted the _ var
			break ;
	}
	temp_2 = temp->next;
	newNode = malloc(sizeof(t_env_list));
	newNode->full = str;
	newNode->var = ft_get_var(str);
	newNode->content = ft_get_content(str);
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
void	ft_export_node(t_env_list **env_head, char *str)
{
	char	**nodes;
	int		i;
	
	if (str[0] == '\0')
	{
		ft_sort_env(*env_head);
		return ;
	}
	if (ft_strchr(str, ' '))
	{
		nodes = ft_split(str, ' ');
		i = 0;
		while(nodes[i])
		{
			ft_add_export(env_head, nodes[i]);
			i++;
		}
		// ft_free2(nodes);
		return ;
	}
	ft_add_export(env_head, str);
	return ;
}
