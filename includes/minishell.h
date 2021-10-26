/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wollio <wollio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 19:22:31 by wollio            #+#    #+#             */
/*   Updated: 2021/10/26 19:58:52 by wollio           ###   ########.fr       */
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
#include <signal.h>

# define PIPE 1 // |
# define OUT 2 // >
# define IN 3 // <
# define LEFT 4 // <<
# define RIGHT 5 // >>
# define BUILT 6
# define SYS 7

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
	char				*file;
	int					op;
	int					flag;
	struct s_parse		*next;
}			t_parse;

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
int		ft_operator(char *str, t_parse **parse); //search for any operator in a string, and return the int corresponding
void	ft_get_env_list(char **envp, t_env_list **env_head);
char	*ft_get_content(char *full);
char	*ft_get_var(char *full);

/** HELPER **/
void	ft_print_list(t_env_list *head);
void	ft_print_list_parse(t_parse *head); // print the list
void	ft_addback_parse(t_parse **head_ref, char *str, int nbr); // create the list
void	ft_free_list_parse(t_parse **head_a); // free the whole list
void	ft_init_parse(t_parse **head); // for each new node created
t_parse	*ft_get_list(t_parse *parse_list); //get parse list from everywhere
t_parse	*ft_get_last(t_parse **head); // return the last node of the list
void	ft_print_node(t_parse *tmp); // print a node

#endif
