/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 07:34:54 by alpicard          #+#    #+#             */
/*   Updated: 2024/01/10 11:37:53 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	dup2_0(t_token *token)
{
	close(token->p_fd[1]);
	dup2(token->p_fd[0], 0);
	close(token->p_fd[0]);
}

void	dup2_1(t_token *token)
{
	close(token->p_fd[0]);
	dup2(token->p_fd[1], 1);
	close(token->p_fd[1]);
}

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


void	do_pipe2(t_token *token)
{
	pid_t	pid;

	if (pipe(token->p_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
	{
		dup2_1(token);
		exec(token);
		free_minishell(token->mini);
		exit(0);
	}
	else
	{
		// dup2(1, token->fd_in);
		token->pid = pid;
		dup2_0(token);
		exec_and_stuff(token->next->next);
	}
}