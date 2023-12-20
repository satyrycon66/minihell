/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siroulea <siroulea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:09:09 by siroulea          #+#    #+#             */
/*   Updated: 2023/12/20 12:59:03 by siroulea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_do_pipe3(t_token *token, int p_fd[2])
{
	char	*path;
	char	**here_doc_cmd;

	close(p_fd[0]);
	dup2(p_fd[1], 1);
	close(p_fd[1]);
	close(token->fd_hd);
	path = get_path(token);
	here_doc_cmd = build_heredoc_cmd2(token);
	if (execve(path, here_doc_cmd, env_l_to_dbl_arr(token->mini->env_test)) < 0)
		command_not_found(token->cmd[0]);
	free_minishell(token->mini);
	exit(0);
}

void	do_pipe3(t_token *token)
{
	pid_t	pid;
	int		p_fd[2];

	if (is_empty(token->next->cmd[0]))
		return ;
	if (pipe(p_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
		child_do_pipe3(token, p_fd);
	else
	{
		token->pid = pid;
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		close(p_fd[0]);
		close(token->fd_hd);
		if (token->next->next)
			exec_and_stuff(token->next->next);
		waitpid(token->pid, 0, 0);
		free_child(token->mini);
		exit(0);
	}
}
