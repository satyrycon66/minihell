/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 12:00:20 by alpicard          #+#    #+#             */
/*   Updated: 2024/01/17 15:30:08 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	token_size(t_token *token)
{
	int	size;

	size = 0;
	while (token->cmd[size])
		size++;
	return (size);
}

// char	**build_redir_cmd(t_token *token)
// {
// 	char	**cmd;
// 	int		cmd_no;
// 	int		cmd_index;

// 	cmd_no = 0;
// 	cmd_index = 0;
// 	cmd = malloc(sizeof(char *) * token_size(token));
// 	while (token->cmd[cmd_no])
// 		cmd[cmd_index++] = token->cmd[cmd_no++];
// 	cmd[cmd_index] = NULL;
// 	return (cmd);
// }

void	redir(t_token *token)
{
	// t_token	*temp;
	// // char	*path;
	// // char	**cmd;
	// // char	**env;
	// temp = token;
	if (token->type == REDIR_IN)
		token->fd_out = open(token->next->cmd[0], O_WRONLY | O_CREAT | O_TRUNC,
				0777);
	else
		token->fd_out = open(token->next->cmd[0], O_WRONLY | O_CREAT | O_APPEND,
				0777);
	dup2(token->fd_out, 1);
	// if (token->next && token->next->next_sep[0] == '|')
	// 	do_pipe2(token);
	// else
	if (token->next && (token->next->type == REDIR_IN || token->next->type == REDIR_DBL))
		redir(token->next);
	
	//  path = get_path(token);
	//  cmd = token->cmd;
	//  env = env_l_to_dbl_arr(token->mini->env_test);
	//  // if (token->next->next_sep && token->next->next_sep[0] == '|')
	//  // 	exec_and_stuff(token->next->next);
 	// if ((execve(path, cmd, env) < 0))
	//  	{
	//  		free(cmd);
	//  		command_not_found(token->cmd[0]);
	// 		close(token->fd_hd);
	//  		path = NULL;
	//  		releaser(env);
	//  	}
	
}

char	**build_heredoc_cmd2(t_token *token)
{
	char	**cmd;
	int		i;
	int		cmd_no;
	t_mini *mini;

	mini = get_data();
	i = 0;
	cmd_no = 0;
	token = mini->tokens;
	cmd = malloc(sizeof(char *) * 15);
	if (!ft_strncmp(token->cmd[i], "ls", 3))
		cmd_no++;
	while (token->cmd[cmd_no])
		cmd[i++] = (token->cmd[cmd_no++]);
	cmd[i] = (".temp");
	cmd[i + 1] = NULL;
	return (cmd);
}

int	do_heredoc(t_token *token)
{
	char	**here_doc_cmd;
	char	*path;
	char	**env;
	t_mini *mini;
	
	
	mini = get_data();
	env = env_l_to_dbl_arr(token->env);
	path = get_path(token);
	if (token->next && token->next->type == HEREDOC_T)
		heredoc(token->next);
	here_doc_cmd = build_heredoc_cmd2(mini->tokens);
	if (is_sep(here_doc_cmd[0]))
		return (0);
	else if ((execve(path, here_doc_cmd, env) < 0))
	{
		// releaser(here_doc_cmd);
		// command_not_found(token->cmd[0]);
		close(token->fd_hd);
		// free(path);
		// free_minishell(mini);
		// releaser(env);
	}
	return (0);
}

int	heredoc(t_token *token)
{
	char	*delimiter;
	char	*heredoc_input;
	t_mini * mini;
	
	mini = get_data();
	if (!token->next->cmd[0])
		return (syntax_error());
	delimiter = (token->next->cmd[0]);
	token->fd_hd = open(".temp", O_RDWR | O_CREAT | O_TRUNC, 0777);
	heredoc_input = get_prompt(HEREDOC);
	if (ft_strncmp(heredoc_input, delimiter, ft_strlen(delimiter) + 1))
		ft_putendl_fd(heredoc_input, token->fd_hd);
	while (ft_strncmp(heredoc_input, delimiter, ft_strlen(delimiter) + 1))
	{
		heredoc_input = get_prompt(HEREDOC);
		if (ft_strncmp(heredoc_input, delimiter, ft_strlen(delimiter) + 1))
			ft_putendl_fd(heredoc_input, token->fd_hd);
	}
	// free(heredoc_input);
	// free(delimiter);
	if (token->next && token->next->type == PIPE)
		do_pipe3(token);
	else
		do_heredoc(token);
	close(token->fd_hd);
	return (1);
}
