#ifndef MINISHELL_H
# define MINISHELL_H

/* Clear the shell */
#define clear() printf("\033[H\033[J")

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/param.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
#include "stdbool.h"
#include <signal.h>
#include <errno.h>

/** OP VARIABLE **/
# define CMD 0
# define PIPE 1
# define OUT 2
# define IN 3
# define LEFT 4
# define RIGHT 5

/** FLAG VARIABLE **/
# define BUILT 6
# define SYS 7
# define FILE 8

/** FLAG for child_builtin **/
# define EX 9
# define RET 10

extern int	exit_status;
typedef struct	s_env
{
	char				*full;
	char				*var;
	char				*content;
	struct s_env		*next;
}			t_env;

typedef struct	s_parse
{
	char				*str;
	char				**cmd;
	int					op;
	int					pipe_flag;
	struct s_parse		*prev;
	struct s_parse		*next;
}			t_parse;

typedef struct s_exec
{
	int		pipes[2];
	pid_t	pid;
	int		temp_fd;
	int		stout;
	int		stin;
	int		outfile;
	int		infile;
	int		cmdcount;
	int		waitcount;
	int		child_status;
	int		breakout;

	int		ret;
	int		out_action;
}			t_exec;

typedef struct s_sys
{
	char	**paths;
	char 	**split;
	char	**split2;
	char	*pathname;
	char	*cmdpath;
	char 	*join_space;
	char 	*join_arg;
	char 	*join_str;
	int		rows;
	int		x;
}			t_sys;

typedef struct s_replace
{
	int		i;
	int		start;
	char	*var;
	char	*content;
	char	*tofree;
	int		quote_flag;
	int		double_flag;
}			t_replace;

typedef struct s_quotes
{
	int		flag_single;
	int		flag_double;
	int		i;
	int		x;
	int		i1;
	int		i2;
	int		pos1;
	char	*temp1;
	char	*temp2;
	char	*temp3;
	char	*temp4;
	char	*temp5;
}			t_quotes;

typedef struct s_lexer
{
	int		i;
	int		op;
	int		loopflag;
	int		quote_flag;
	char	*str;
	int		pipe_flag;
}			t_lexer;

typedef struct s_split
{
	int		flag;
	size_t	i;
	size_t	t;
	size_t	h;
	char	**mat;
}			t_split;

typedef struct s_order
{
	t_env	*newNode;
	t_env	*temp1;
	t_env	*temp2;
}			t_order;

typedef struct s_cd
{
	char	*old;
	char	*current;
}			t_cd;

/** INIT **/
void	ft_silience(char **envp); // hide ^C when hiting control+C
void	ft_init(int argc, char **argv, char **envp, t_env **env_head); // initialize the shell
void	ft_sigint(int signal); // handle ctrl + c
void	ft_tool(int *fd_in_old, int *fd_out_old); // contain signal handling and fd dup

/** BUILDINS FUNCTION **/ /** ALL OF THESE HAVE TO STAY **/
void	ft_echo(char **cmd);
void	ft_cd(t_env **env_head, char  *line);
void	ft_reset_paths(t_env **env_head, char *current, char *old); // reset current old 
void	ft_free_current_old(char **current, char **old); // free current old string
void	ft_init_cd(t_cd *cd, t_env **env_head); // init cd vars
void	ft_change_env_var(t_env **env_head, char *change, char *new); // changes env vars after cding
void	ft_pwd(void);
void	ft_exit(t_parse *parse);
void	ft_unset_node(t_env **env_head, char **cmd);
void	ft_export_node(t_env **env_head, char **cmd);
int		ft_export_edgecase(char *str);
void	ft_delete_node(t_env **env_head, char *str);
void	ft_env(t_env *env_head);

/** EXECUTION **/ /** ALL OF THESE HAVE TO STAY **/
void	ft_execution(t_parse *parse, char **envp, t_env **env_head); // main of pipex part
int		ft_is_builtin_new(char *line); // checks if command is abuiltin
void	ft_child_for_built(t_parse *parse, t_env **env_head, int status); // execute builtin commands
void	ft_parent(t_exec *exec); // output of last commands pipe will now ne in temp_fd
void	ft_in_is_tempfd(t_exec *exec); // childs always read from temp_fd --> redirect temp_fd to be input
int		ft_redirect_in(t_exec *exec, t_parse **parse); // takes input either from infile or stdin
void	ft_write_to_pipe(t_exec *exec); // sets pipe to stdout
int		ft_file_only(t_parse *parse, t_exec *exec); // when there are only files in parse, open all of them
int		ft_write_here(t_parse *parse, t_exec *exec); // write to outfile, pipe or stdout
int		ft_choose_outfile(t_exec *exec, t_parse *parse); // open all outfiles and set last one to stdout
int		ft_pipe(t_exec *exec); // creates a pipe for interprocess communication
int		ft_fork(t_exec *exec); // fork a process
int		ft_heredoc(t_exec *exec, t_parse *parse); //opens heredoc, that waits fors limiter
void	ft_child_for_sys(t_parse *parse, char **envp, t_env **env_head); // execute system commands
int		ft_countrows(char **paths); // counts rows in a 2d array
void	ft_close_all(t_exec *exec); // closes all existing file-descriptors
int		ft_count_cmds(t_parse *parse); // counts cmds for every parse
void	ft_init_exec(t_exec *exec, t_parse *parse); // init struct variables
void	ft_wait(t_exec exec); // waits for all childs to finish executing
int		ft_catch_trash(t_parse *parse, t_exec *exec); // checks for empty list and if there are even cdms inn the list



/** ERROR MANAGEMENT **/
void	ft_error(char *line);
int		ft_pipe_error(int i, t_parse **parse, char **arr, int op); // check if there is an error when encountering a pipe
int		ft_first(char **paths, int i, t_parse **parse, char **arr); // check if there is an error when reading the first
void	ft_msg_cmd(char *arr); // display message error when command not found
void	ft_msg_pars(char *arr); // display message error when encountering a parse error
void	ft_msg_arg(char *arr); // display message error when encountering an option with a built-in

/* PARSING */
void	ft_get_env_list(char **envp, t_env **env_head); // turns env variable into a list
char	*ft_get_content(char *full); // returns content from env string
char	*ft_get_var(char *full); // returns var from env string
char	**ft_line_path(char **envp); // line where PATH is in env
void	ft_bef(t_parse **parse, char *line, int *x); // skip spaces
void	ft_after(t_parse **parse, char *line, int *x); // skip spaces
int		ft_caller_builtin(t_parse **parse, char *line, int *x); // call the function ft_is_buildin and creates a node if necessary
int		ft_is_builtin(char *line, int x, int *y); // check if the command is built-in
int		ft_strncmp2(const char *str1, const char *str2, int x, int *i); // takes a pointer as in index
int		ft_op(const char *line, int i); // look for operators
int		ft_caller_sys_fct(t_parse **parse, char **paths, char *line, int *x); // call the function checkcommand
char	*ft_clean_sys_fct(char *line, int *x, int *y); // cleaner for builtin
void	ft_operator_bef(t_parse **parse, char *line, int *x); //handle cases where operator appears before functions cmd
int		ft_operator_after(t_parse **parse, char *line, int *x); //handle cases where operator appears after functions cmd
void	ft_file_bef(t_parse **parse, char *line, int *x, int op); // Initialize str file if needed
void	ft_file_after(t_parse **parse, char *line, int *x, int op);
void	ft_arg(t_parse **parse, char *line, int *x); // initialize arg variables
void	ft_arg_tool(t_parse *last, char *line, int *x); // tool of the ft_arg
void	ft_arg_error(t_parse *last, t_parse **parse, int *x, char *line); // manage error cases in ft_arg
void	ft_str(t_parse **parse, char *line, int *x); // initialize str variables


/** NEW PARSING *********************************************************************************************************/
int		ft_parsing(char *line, t_parse **parse, t_env **env_head); // general function
int		ft_lexer(char *line, t_parse **parse); // create tokens (splitting on special chars and ignoring them if quoted)
void	ft_convert_dollar(t_parse **parse, t_env *env_head); // searches for a $VAR in str of the Node and replaces it with content
void	ft_seperator(t_parse **parse); // puts the tokens in the right order and changes content if necessary
void	ft_splitter(t_parse **parse); // create 2D arrays out of strings in every function
char	**ft_split2(char const *s, char c,  int *count); // only split, when char is not quoted

// utils
void	ft_add_next(t_parse **head_ref, t_parse *previous, char **str, int nbr);
int		ft_operator_tool(char *str, int *x); // looks for operator, return its value and increment the index
int		ft_operator_tool2(char *str, int *x); // looks for operator and return its value
void	ft_skip_space(char *line, int *x); // ignores spaces
int		countrows(char **paths); // count rows in paths
void	ft_append(char **last_arg, char **arg); // append strings in the variables

void	ft_quotes(t_parse **parse);

void	sigfunc_child(int sig);
int		ft_variable_pid(int pid);

/** HELPER **/
void	ft_print_list(t_env *head);
//void	ft_print_list_parse(t_parse **head); // print the list
//void	ft_print_list_parse_2(t_parse **head);
void	ft_addback_parse(t_parse **head_ref, char *str, int nbr, int *pipe_flag); // create the list
void	ft_free_list_parse(t_parse **head_a); // free the whole list
void	ft_init_parse(t_parse **head); // for each new node created
t_parse	*ft_get_list(t_parse *parse_list); //get parse list from everywhere
t_parse	*ft_get_last(t_parse **head); // return the last node of the list
//void	ft_print_node(t_parse *tmp); // print a node
//void	ft_print_last(t_parse **head); // print last node
char	*ft_extract_content(t_env *env_head, char *var); // returns the value of the env variable you pass in to it
void	ft_system_executer(char *str, char **envp); // execute any bash command by passing the cmd string as str and env as envp
void	ft_addorder(t_env **head, char *str); // add elements in alphabetical order to list
void	ft_addfront(t_env **head, char *str); // add element to front of list
void	ft_addback_sorted(t_env **head, char *str); // variation of addback for sorting the list
void	ft_free_list(t_env **head_a);

/* NEW HELPER */
char	**ft_get_paths(char **paths); // static function to get paths variable

#endif
