/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wollio <wollio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 19:22:31 by wollio            #+#    #+#             */
/*   Updated: 2021/10/30 18:23:50 by wollio           ###   ########.fr       */
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
#include <signal.h> // for the signal function
#include <errno.h> // for errno var

/** OP VARIABLE **/
# define PIPE 1 // |
# define OUT 2 // >
# define IN 3 // <
# define LEFT 4 // <<
# define RIGHT 5 // >>

/** FLAG VARIABLE **/
# define BUILT 6
# define SYS 7
# define FILE 8

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
	int					op;
	int					flag;
	struct s_parse		*prev;
	struct s_parse		*next;
}			t_parse;

/** INIT **/
void	ft_silience(char **envp); // hide ^C when hiting control+C
void	ft_init(int argc, char **envp, t_env_list **env_head); // initialize the shell

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
int		check_commandpath(char **paths, char *cmd); // check if it's a system function
char	**ft_line_path(char **envp); // line where PATH is in env
int		ft_is_builtin(char *s); // check if the command is built-in
int		ft_operator(int i, t_parse **parse, char **arr); //handle cases where operator appears
int		ft_operator_tool(int i, char **arr); //search for any operator in a string, and return the int corresponding
void	ft_file(int i, t_parse **parse, char **arr, int op); // Initialize str file if needed
int		ft_arg(int i, t_parse **parse, char **arr); // search for arguments
int		ft_first(char **paths, int i, t_parse **parse, char **arr); // read the first input
void	ft_cmd(int i, t_parse **parse, char **arr); // look at the following variables when encountering a cmd
void	ft_get_env_list(char **envp, t_env_list **env_head);
char	*ft_get_content(char *full);
char	*ft_get_var(char *full);

/** HELPER **/
void	ft_print_list(t_env_list *head);
void	ft_print_list_parse(t_parse *head); // print the list
void	ft_print_list_parse2(t_parse **head); // print the list with the previous
void	ft_addback_parse(t_parse **head_ref, char *str, int nbr); // create the list
void	ft_free_list_parse(t_parse **head_a); // free the whole list
void	ft_init_parse(t_parse **head); // for each new node created
t_parse	*ft_get_list(t_parse *parse_list); //get parse list from everywhere
t_parse	*ft_get_last(t_parse **head); // return the last node of the list
void	ft_print_node(t_parse *tmp); // print a node

#endif
