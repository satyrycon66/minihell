/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:09:09 by siroulea          #+#    #+#             */
/*   Updated: 2024/01/17 15:41:19 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_do_pipe3(t_token *token)
{
	t_mini *mini;

	mini = get_data();
	close(token->p_fd[0]);
	dup2(token->p_fd[1], 1);
	close(token->p_fd[1]);
		// printf("TEST1\n");
	do_heredoc(token);
	free_minishell(token->mini);
	exit(0);
}

void	do_pipe3(t_token *token)
{
	pid_t	pid;
	// int		p_fd[2];

	if (is_empty(token->next->cmd[0]))
		return ;
	if (pipe(token->p_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid){

		token->pid = pid;
		close(token->p_fd[1]);
		dup2(token->p_fd[0], 0);
		close(token->p_fd[0]);
		close(token->fd_hd);
		waitpid(pid, 0, 0);
		printf("TEST\n");
		while (token->next != NULL)
			token = token->next;
		exec(token);
		free_child(token->mini);
		exit(0);
	}
	else
	{
		child_do_pipe3(token);
	}
}
