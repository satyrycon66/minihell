/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siroulea <siroulea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:33:40 by siroulea          #+#    #+#             */
/*   Updated: 2023/12/13 12:34:56 by siroulea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_chain(t_mini *mini, int cmd_index)
{
	int		x;
	t_token	*head;

	x = 1;
	head = mini->tokens;
	if (is_sep(mini->cmds[cmd_index]))
		cmd_index++;
	while (cmd_index < mini->no_wrds || mini->cmds[cmd_index] != NULL)
	{
		if (is_sep(mini->cmds[cmd_index]) && mini->cmds[cmd_index + 1]
			&& cmd_index)
			cmd_index++;
		mini->tokens->next = init_tokens(mini, cmd_index, x++);
		mini->tokens = mini->tokens->next;
		while (mini->cmds[cmd_index] && !is_sep(mini->cmds[cmd_index]))
			cmd_index++;
		if ((mini->cmds[cmd_index]))
			mini->tokens->next_sep = ft_strdup(mini->cmds[cmd_index]);
		else
			mini->tokens->next_sep = NULL;
	}
	mini->tokens = head;
}

void	tokens_next_sep(t_token *tokens)
{
	if (!ft_strncmp(tokens->next_sep, "|", 2))
		tokens->type = PIPE;
	else if (!ft_strncmp(tokens->next_sep, "<<", 3))
		tokens->type = REDIR_DBL2;
	else if (!ft_strncmp(tokens->next_sep, ">>", 3))
		tokens->type = REDIR_DBL;
	else if (!ft_strncmp(tokens->next_sep, ">", 2))
	{
		tokens->type = REDIR_IN;
		if (tokens->next && tokens->next->next_sep == NULL)
			tokens->next->type = -1;
	}
}

void	token_type(t_token *tokens)
{
	if (tokens->next_sep)
		tokens_next_sep(tokens);
	else
		tokens->type = 1;
	if (!ft_strncmp(tokens->cmd[0], "<", 2))
		tokens->type = REDIR_OUT;
	if (!ft_strncmp(tokens->cmd[0], ">", 2))
	{
		tokens->type = REDIR_IN;
		redir(tokens);
	}
	else if (tokens->cmd && (tokens->cmd[0][0] == '.'
		|| tokens->cmd[0][0] == '/'))
		tokens->type = ABS;
}

int	get_types(t_mini *mini)
{
	t_token	*head;

	head = mini->tokens;
	while (mini->tokens != NULL)
	{
		if (mini->tokens->type >= 0)
			token_type(mini->tokens);
		mini->tokens = mini->tokens->next;
	}
	mini->tokens = head;
	return (1);
}

int	tokeniser(t_mini *mini)
{
	int		x;
	t_token	*head;
	int		cmd_index;

	x = 0;
	cmd_index = 0;
	mini->tokens = init_tokens(mini, cmd_index, x);
	head = mini->tokens;
	while (mini->cmds[cmd_index] && !is_sep(mini->cmds[cmd_index]))
		cmd_index++;
	if (mini->cmds[cmd_index] && is_sep(mini->cmds[cmd_index]))
		mini->tokens->next_sep = ft_strdup(mini->cmds[cmd_index]);
	else
		mini->tokens->next_sep = NULL;
	ft_chain(mini, cmd_index);
	mini->tokens = head;
	releaser(mini->cmds);
	if (!get_types(mini))
		return (0);
	return (1);
}
