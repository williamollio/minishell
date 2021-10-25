/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wollio <wollio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 19:22:31 by wollio            #+#    #+#             */
/*   Updated: 2021/10/25 19:31:04 by wollio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Clear the shell */
#define clear() printf("\033[H\033[J")

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
#include "stdbool.h" // for boolean variable type

typedef struct	s_env_list
{
	char				*full;
	char				*var;
	char				*content;
	struct s_env_list	*next;
}			t_env_list;

typedef struct	s_parse
{
	char				*cmd;
	char				*arg;
	char				*str;
	bool				pipe;
	bool				out; // >
	bool				in; // <
	bool				left; // <<
	bool				right; // >>
	struct s_parse		*next;
}			t_parse;

int main();

/** BUILDINS FUNCTION **/
void	ft_echo(char  *line);
void	ft_cd(char  *line);
void	ft_pwd(char  *line);
// void	ft_export(char  *line);
// void	ft_unset(char  *line);
// void	ft_env(char **envp);
void	ft_exit(void);
void	ft_export_node(t_env_list **env_head, char *str);
void	ft_delete_node(t_env_list **env_head, char *str);

/** SYSTEM FUNCTION **/
void	ft_sys_funct_ex(char *line);
void	ft_sys_funct_chck(char *line);

/** ERROR MANAGEMENT **/
void	ft_error(char *str);

/** PARSE **/
void	ft_parsing(char **envp, char *line, t_parse **parse); // general function
char	**ft_line_path(char **envp, char **paths); // line where PATH is in env
int		ft_is_builtin(char *s); // check if the command is built-in
void	ft_get_env_list(char **envp, t_env_list **env_head);
char	*ft_get_content(char *full);
char	*ft_get_var(char *full);

//** HELPER **/
void	ft_print_list(t_env_list *head);
void	ft_print_list_parse(t_parse *head);
void	ft_addback_parse(t_parse **head_ref, char *str);

#endif
