/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:09:24 by siroulea          #+#    #+#             */
/*   Updated: 2024/01/14 15:18:44 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	do_child_stuff(t_token *token)
{
	if (token->type == REDIR_IN)
		redir(token);
	else if (token->type == REDIR_OUT)
		redir2(token);
	else if (token->type == REDIR_DBL2)
		heredoc(token);
	else if (token->type == REDIR_DBL)
		redir(token);
	else if (token->type == -3)
		do_pipe3(token);
	else if (token->type == PIPE || ft_strncmp(token->next_sep, "|", 1))
		do_pipe(token);
	else if (token->type == ABS)
		absolute_path(token);
	else if (!ft_strncmp(token->cmd[0], "echo", 5))
		ft_echo(token);
	else if (!ft_strncmp(token->cmd[0], "pwd", 4))
		ft_pwd(token);
	else
		exec(token);
	free_child(token->mini);
	exit(0);
}

void	exec_and_stuff(t_token *token)
{
	t_token	*head;
	t_mini	*mini;
	pid_t	pid;

	mini = get_data();
	if (token == NULL)
		return ;
	head = token;
	if (is_empty(token->cmd[0]))
	{
		command_not_found(token->cmd[0]);
		if (token->next)
			exec_and_stuff(token->next);
	}
	else if (!ft_builtins(head))
	{
		pid = fork();
		if (!pid)
			do_child_stuff(head);
		else
		{
			head->child_pid = pid;
			wait_pids(mini->tokens);
		}
		if (token->next && token->next->next && token->type == REDIR_IN)
			exec_and_stuff(token->next->next);
	}
}
