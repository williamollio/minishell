#include "../../includes/minishell.h"

// int	ft_get_pos1_pos2(int *pos1, int *pos2, char *str)
// {
// 	int	x;
// 	int	flag;

// 	flag = 0;
// 	x = 0;
// 	while (str[x])
// 	{
// 		if (str[x] == '"' && flag == 0)
// 		{
// 			*pos1 = x;
// 			flag = 1;
// 		}
// 		else if (str[x] == '"' && flag == 1)
// 		{
// 			*pos2 = x;
// 			flag = 2;
// 		}
// 		x++;
// 	}
// 	if (flag == 0)
// 		return (1);
// 	// if (flag != 2)
// 	// 	ft_putendl_fd("unclosed quotes!", 2); // i think we already do that somewhere
// 	return (0);
// }

// char	*ft_join(char *s1, char *s2)
// {
// 	char	*res;

// 	if (!s1)
// 	{
// 		res = ft_strdup(s2);
// 		free(s2);
// 	}
// 	else if (!s2)
// 	{
// 		res = ft_strdup(s1);
// 		free(s1);
// 	}
// 	else
// 	{
// 		res =  ft_strjoin(s1, s2);
// 		free(s1);
// 		free(s2);
// 	}
// 	return (res);
// }

// char	*ft_remover(char *str, int pos1, int pos2)
// {
// 	char	*sub1;
// 	char	*sub2;
// 	char	*sub3;
// 	char	*temp;
// 	char	*res;

// 	if (pos1 == 0)
// 	{
// 		sub1 = ft_substr(str, pos1 + 1, pos2 - pos1 - 1);
// 		sub2 = ft_substr(str, pos2 + 1, ft_strlen(str) - pos2);
// 		res = ft_join(sub1, sub2);
// 	}
// 	else
// 	{
// 		sub1 = ft_substr(str, 0, pos1);
// 		sub2 = ft_substr(str, pos1 + 1, pos2 - pos1 - 1);
// 		sub3 = ft_substr(str, pos2 + 1, ft_strlen(str) - pos2);
// 		temp = ft_join(sub1, sub2);
// 		res = ft_join(temp, sub3);
// 	}
// 	printf("res = %s\n", res);
// 	free(str);
// 	return (res);
// }

// char *ft_remove_quotes(char *str)
// {
// 	// int		i;
// 	int		pos1 = 0;
// 	int		pos2 = 0;
// 	char	*res;
// 	// int		flag_single;
// 	// int		flag_double;

// 	// flag_single = 1;
// 	// flag_double = 1;
// 	while (1)
// 	{
// 		if (ft_get_pos1_pos2(&pos1, &pos2, str))
// 			break ;
// 		printf("pos1 = %d\npos2 = %d\n", pos1, pos2);
// 		str = ft_remover(str, pos1, pos2);
// 	}
// 	res = str;
// 	// free(str);
// 	return (res);
// }

// void ft_quotes(t_parse **parse)
// {
// 	t_parse *tmp;
// 	int		i;

// 	tmp = *parse;
// 	while (tmp != NULL)
// 	{
// 		i = 0;
// 		while (tmp->cmd[i])
// 		{
// 			if (ft_strnstr(tmp->cmd[i], "'", ft_strlen(tmp->cmd[i])) != 0 || ft_strchr(tmp->cmd[i], '"') != NULL)
// 			{
// 				printf("tmp->cmd[i] : %s\n", tmp->cmd[i]);
// 				tmp->cmd[i] = ft_remove_quotes(tmp->cmd[i]);
// 			}
// 			i++;
// 		}
// 		tmp = tmp->next;
// 	}
// }

int ft_parsing(char **envp, char *line, t_parse **parse, t_env_list **env_head)
{
	*parse = NULL;

	(void)envp;
	if (ft_lexer(line, parse) < 0)
	{
		ft_putendl_fd("unclosed quotes", 2);
		// return error here
	}
	// printf("after lexer: -------------------------\n");
	// ft_print_list_parse_2(parse);
	// printf("----------------------------\n\n\n\n\n");


	ft_convert_dollar(parse, *env_head);

	// printf("after dollar: -------------------------\n");
	// ft_print_list_parse_2(parse);
	// printf("----------------------------\n\n\n\n\n");

	ft_seperator(parse);

	// printf("after seperator: -------------------------\n");
	// ft_print_list_parse_2(parse);
	// printf("----------------------------\n\n\n\n\n");

	t_parse 	*temp = *parse;

	while (temp != NULL)
	{
		temp = temp->next;
		if (temp == NULL)
			break ;
		if (temp->op == 1 && (temp->prev->op >= 2 && temp->prev->op <= 5))
		{
			temp->op = 0;
			// temp->pipe_flag = 1;
		}
	}

	ft_splitter(parse);
	// printf("after splitter: -------------------------\n");
	// ft_print_list_parse_2(parse);
	// printf("----------------------------\n\n\n\n\n");
	// ft_quotes(parse);

	return (EXIT_SUCCESS);
}
