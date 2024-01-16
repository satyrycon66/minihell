/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:37:50 by alpicard          #+#    #+#             */
/*   Updated: 2024/01/16 16:04:27 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Readline/history.h"
# include "../Readline/readline.h"
# include "../libft/include/libft.h"
# include <fcntl.h>
# include <pthread.h>
# include <signal.h>
# include <stdint.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/_types/_errno_t.h>
# include <ctype.h>



# define PROMPT "Minishell-1.0$ "
# define HEREDOC "heredoc > "
//Token types 0-10
# define EMPTY 0
# define CMD 1
# define ARGS 2
# define PIPE 3        // |
# define REDIR_IN 4    // >
# define REDIR_OUT 5   // <
# define REDIR_DBL 9   // >>
# define REDIR_DBL2 10 // <<
# define ABS 6
# define FILE_OUT 7

//Modes 11-12
# define INTERACTIVE 11
# define CHILD 12

typedef struct s_token
{
	int					token_no;
	int					type;
	char				**cmd;
	char				*next_sep;
	int					errno;
	int					errnum;
	pid_t				child_pid;
	pid_t				pid;
	int					p_fd[2];

	int					input;
	int					output;
	int					fd_in;
	int					fd_out;
	int					fd_hd;
	struct s_environ	*env;
	struct s_mini		*mini;
	struct s_token		*next;
}						t_token;

typedef struct s_mini
{
	char				*input;
	char				**cmds;
	int					no_sep;
	int					no_wrds;
	char				**env;
	char				*shlvl;
	char				*path;
	int					env_len;
	struct s_environ	*env_test;
	struct s_export	*export;
	int					errno;
	struct s_token		*tokens;
	int					pid;
}						t_mini;

typedef struct s_environ
{
	char				**temp;
	char				*env_var;
	char				*env_val;
	int					num;
	struct s_environ	*next;
}						t_environ;

typedef struct s_export
{
	char				**temp;
	char				*env_var;
	char				*env_val;
	struct s_export		*next;
}						t_export;

int						g_errno;

/*Builtins*/
int						ft_echo(t_token *token);
int						ft_pwd(t_token *token);
int						ft_env(t_token *token);
void					set_env(t_mini *mini, char **env);
int						ft_cd(t_mini *mini, t_token *token);
int						update_env_part(t_mini *mini, char *part, char *_new);
int						update_env_part2(t_mini *mini, char *part, char *_new);
char					*get_env_part(t_mini *mini, char *part);
int						ft_unset(t_token *token);
int						ft_export(t_mini *mini, char **var);
int						ft_export2(t_mini *mini, char **var);
int						ft_builtins(t_token *token);
int						is_builtin(t_token *token);

/*Parse*/
t_token	*init_tokens(t_mini *mini, int cmd_index, int x);
int						ft_parse(t_mini *mini);
int						parse_mini_cmds(t_mini *mini);
int						is_empty(char *input);
int is_char_sep(int c);
int						has_equal_sign(char **var);
int						tokeniser(t_mini *mini);
char					**env_l_to_dbl_arr(t_environ *env);
char					*check_part(char *part);
int						check_pipe(t_mini *mini, int cmd_no);
int						check_valid_quotes(char *input);
void					set_err_code(int code);
int						has_dollar_sign(char *input);
char					*dollar_sign(char *mini_cmd);
int						has_quotes(char *str);
int token_size(t_token *token);

/*Env*/

int	set_shlvl(void);
t_environ				*new_env(char **var);
t_environ				*new_env2(char *var);
t_environ				*new_env_list(char *content);
t_environ				*ft_envlast(t_environ *env);
t_environ				*init_env_list(t_mini *mini, int env_item);
t_environ				*init_item(char *to_split);
void					ft_envadd_back(t_environ **env, t_environ *neo);
void					print_env(t_environ *environ);
void					do_export(t_mini *mini, t_export *_export, char **var);
int						ft_set_env(t_mini *mini, char **env);
int						export_no_input(t_mini *mini);
int						check_export(char **var);
t_export				*init_export(t_mini *mini, char **var);

/*Mini_split*/
int						no_of_words(char *s, int trigger, int i, int no_wrds);
int						word_len(char *s, int start);
char					**mini_split(char *s);
char					**ft_split2(char const *s, char *c);

/*Execute*/
t_mini					*get_data(void);
void					exec_and_stuff(t_token *token);
char					*get_path(t_token *token);
void					absolute_path(t_token *token);
int						exec(t_token *token);
void					wait_pids(t_token *token);
void					wait_c_pids(t_token *token);
int						heredoc(t_token *token);
void					do_pipe3(t_token *token);
void					do_pipe2(t_token *token);
void					do_pipe(t_token *token);
void					do_pipea(t_token *token);
void					redir(t_token *token);
void					redir2(t_token *token);
void					redir_append(t_token *token);
char					**build_heredoc_cmd2(t_token *token);

/*Utils*/
char					*get_prompt(char *prt);
int						ft_len(char *s);
int						is_sep(char *str);
int						no_of_quotes(int max, char *s);
int						no_of_squotes(int max, char *s);
char					*ft_str_to_upper(char *s);
int						is_quoted(char *str);
int						is_quote(int c);

/*Display test*/
void					print_array(t_mini *mini);
void					prt_array(t_mini *mini);
void					display_split(char **s, char *str);
void					print_token(t_mini *mini);
void					print_env_l(t_mini *mini);

/*Signals*/
void					init_signals(int mode);
void					ft_handler(int sig);
void					handler(int sig, siginfo_t *info, void *s);

/*Errors*/
int						syntax_error(void);
int						invalid_path(char *error);
int						command_not_found(char *error);
int						is_a_directory(char *error);
void					set_err_code(int code);

/*Free*/
void					*releaser(char **table);
void					free_tokens(t_token *tokens);
void					free_env(t_environ *env);
int						free_minishell(t_mini *mini);
void					reset_minishell(t_mini *mini);
void					free_export(t_export *exp);
void					free_child(t_mini *mini);

#endif