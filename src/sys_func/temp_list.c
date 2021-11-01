// #include "../../includes/minishell.h"

// void	ft_print_list_test(t_parse *head)
// {
// 	while (head != NULL)
// 	{
// 		printf("%s\n", head->cmd);
// 		// printf("%s\n", head->cmd_only);
// 		// printf("%s\n", head->operator);
// 		head = head->next;
// 	}
// }

// // just temporary for dummy parse list
// void	ft_addlist(t_parse **head_ref, char *s1, char *s2, int op, int flag, char *string)
// {
// 	t_parse	*newNode;
// 	t_parse	*last;

// 	last = *head_ref;
// 	newNode = malloc(sizeof(t_parse));
// 	newNode->arg = s1;
// 	newNode->cmd = s2;
// 	newNode->str = string;
// 	newNode->op = op;
// 	newNode->flag = flag;
// 	newNode->next = NULL;
// 	if (*head_ref == NULL)
// 	{
// 		*head_ref = newNode;
// 		return ;
// 	}
// 	while (last->next != NULL)
// 		last = last->next;
// 	last->next = newNode;
// 	return ;
// }

// void	ft_make_test_list(t_parse **test_head)
// {
// 	char	*args_1;
// 	char	*cmd_1;
// 	int		op_1;
// 	int		flag_1;

// 	char	*args_2;
// 	char	*cmd_2;
// 	int		op_2;
// 	int		flag_2;

// 	char	*args_3;
// 	char	*cmd_3;
// 	int		op_3;
// 	int		flag_3;
// 	char	*str_3;

// 	//1st cmd node
// 	cmd_1 = "ls";
// 	args_1 = "";
// 	op_1 = PIPE;
// 	flag_1 = SYS;

// 	//2nd cmd node
// 	cmd_2 = "cat";
// 	args_2 = "-e";
// 	op_2 = 0;
// 	flag_2 = SYS;

// 	//3rd cmd node
// 	cmd_3 = "cat";
// 	args_3 = "-e";
// 	str_3 = "out.txt"; //currently this is the outfile, but the problem is, that its in the same node as command
// 	op_3 = 0; // 0 if you want to wriite to stdout, you can also change to "OUT" or "RIGHT"
// 	flag_3 = SYS;

// 	//creating dummy list
// 	// ft_addlist(test_head, NULL, NULL, IN, 0, "Makefile"); //if you uncomment this, Makefile will be inputfile
// 	ft_addlist(test_head, args_1, cmd_1, op_1, flag_1, NULL);
// 	ft_addlist(test_head, args_2, cmd_2, op_2, flag_2, NULL);//pass str_2 instead of NULL to write in outfile
// 	// ft_addlist(test_head, args_3, cmd_3, op_3, flag_3, NULL);

// 	// ft_print_list_test(*test_head);
// }