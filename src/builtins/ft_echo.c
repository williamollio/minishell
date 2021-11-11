// #include "../../includes/minishell.h"

// // the commented part is unnecessary ifwilliam includes '$' in parsing
// void	ft_echo(char *str, char *arg)
// {
// 	char	*join_space;
// 	char	*join_str;
// 	char	*strn;
// 	// char	*pass;
	
// 	// if (str[0] == '$')
// 	// {
// 	// 	noDollar = ft_substr(str, 1, ft_strlen(str) - 1);
// 	// 	pass = ft_extract_content(env_head, noDollar);
// 	// }
// 	// else
// 	// 	pass = ft_strdup(str);
// 	strn = ft_strnstr(str, "$?", ft_strlen(str));
// 	if (ft_strncmp(arg, "-n", 2) == 0 && ft_strlen(arg) == 2)
// 	{
// 		if (strn) // makes way more sense if william just does that in parsing
// 			printf("%d", exit_status);
// 		else
// 			printf("%s", str);
// 	}
// 	else if (arg[0] == '\0')
// 	{
// 		if (strn) // makes way more sense if william just does that in parsing
// 			printf("%d\n", exit_status);
// 		else
// 			printf("%s\n", str);
// 	}
// 	else
// 	{
// 		join_space = ft_strjoin(arg, " ");
// 		join_str = ft_strjoin(join_space, str);
// 		free(join_space);
// 		if (strn) // makes way more sense if william just does that in parsing
// 			printf("%d\n", exit_status);
// 		else
// 			printf("%s\n", join_str);
// 		free(join_str);
// 	}
// 	free(strn);
// 	// free(pass);
// }
