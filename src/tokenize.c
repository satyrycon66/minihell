/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:52:40 by alpicard          #+#    #+#             */
/*   Updated: 2024/01/20 19:14:03 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_cmd(t_token *token)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;

	i = -1;
	if (get_env_part(token->mini, "PATH") == NULL)
		return (1);
	allpath = ft_split(get_env_part(token->mini, "PATH"), ':');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, token->cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			free(exec);
			g_errno = 0;
		}
		else
		{
			free(exec);
			g_errno = 127;
		}
	}
	releaser(allpath);
	return (g_errno);
}

int	check_file_exists(t_token *token)
{
	if (token->cmd && token->cmd[1])
	{
		if (token->cmd[1][0] != '-')
		{
			if (access(token->cmd[1], F_OK | X_OK) == 0)
				return (0);
			else
				return (1);
		}
	}
	return (g_errno);
}

int	get_errno(t_token *token)
{
	if (is_builtin(token))
		return (0);
	else if (!ft_strncmp(token->cmd[0], "exit", 5))
		return (g_errno);
	else if (check_cmd(token))
		g_errno = check_cmd(token);
	else if (check_file_exists(token))
		g_errno = 1;
	return (g_errno);
}

void	set_var_tokens(t_mini *mini, t_token *tokens, int x, int wrd_no)
{
	tokens->cmd[wrd_no] = NULL;
	tokens->type = 0;
	tokens->token_no = x;
	mini->no_of_tokens = x;
	// tokens->pid = -1;
	// tokens->child_pid = -1;
	if(!ft_strncmp(tokens->cmd[0],"cat", 4))
		tokens->ex_kind = 1;
	tokens->env = mini->env_test;
	tokens->fd_out = 0;
	tokens->mini = mini;
	tokens->next = NULL;
	tokens->errnum = get_errno(tokens);
}

t_token	*init_tokens(t_mini *mini, int cmd_index, int x)
{
	t_token	*tokens;
	int		wrd_no;

	wrd_no = 0;
	tokens = malloc(sizeof(t_token));
	tokens->cmd = malloc(sizeof(char *) * 100);
	if (!mini->cmds)
		return NULL;
	if (mini->cmds[cmd_index] && is_sep(mini->cmds[cmd_index]))
		tokens->cmd[wrd_no++] = ft_strdup(mini->cmds[cmd_index++]);
	while (mini->cmds[cmd_index] && !is_sep(mini->cmds[cmd_index]) && !is_empty(mini->cmds[cmd_index]))
	{
		if (mini->cmds[cmd_index][0] == '$' && (has_quotes(mini->cmds[cmd_index]) != 2))
			tokens->cmd[wrd_no] = dollar_sign(mini->cmds[cmd_index]);
		else if (!has_quotes(mini->cmds[cmd_index]))
			tokens->cmd[wrd_no] = ft_strdup(mini->cmds[cmd_index]);
		else if ((has_quotes(mini->cmds[cmd_index]) == 2))
			tokens->cmd[wrd_no] = ft_strdup2(mini->cmds[cmd_index]);
		else
			tokens->cmd[wrd_no] = ft_strdup2(mini->cmds[cmd_index]);
		wrd_no++;
		cmd_index++;
	}
	set_var_tokens(mini, tokens, x, wrd_no);
	return (tokens);
}
