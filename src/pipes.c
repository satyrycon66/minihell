/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siroulea <siroulea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 07:34:54 by alpicard          #+#    #+#             */
/*   Updated: 2023/12/18 14:09:41 by siroulea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_do_pipe(t_token *token)
{
	close(token->p_fd[0]);
	dup2(token->p_fd[1], 1);
	close(token->p_fd[1]);
	exec(token);
	free_minishell(token->mini);
	exit(0);
}

void	do_pipe(t_token *token)
{
	pid_t	pid;

	if (is_empty(token->next->cmd[0]))
		return ;
	if (pipe(token->p_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
		child_do_pipe(token);
	else
	{
		token->pid = pid;
		close(token->p_fd[1]);
		dup2(token->p_fd[0], 0);
		close(token->p_fd[0]);
		exec_and_stuff(token->next);
		free_child(token->mini);
		exit(0);
	}
}

void	child_do_pipe2(t_token *token, int p_fd[2])
{
	close(p_fd[0]);
	dup2(p_fd[1], 1);
	close(p_fd[1]);
	free_minishell(token->mini);
	exec(token);
	exit(0);
}

void	do_pipe2(t_token *token)
{
	pid_t	pid;
	int		p_fd[2];

	if (is_empty(token->next->cmd[0]))
		return ;
	if (pipe(p_fd) == -1)
		exit(0);
	pid = fork();
	if (token->pid == -1)
		exit(0);
	if (!pid)
		child_do_pipe2(token, p_fd);
	else
	{
		token->pid = pid;
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		close(p_fd[0]);
		if (token->next->next->cmd)
			exec_and_stuff(token->next->next);
		waitpid(pid, NULL, 0);
	}
}
