/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:09:24 by siroulea          #+#    #+#             */
/*   Updated: 2024/01/20 19:24:21 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <unistd.h>

void	do_child_stuff(t_token *token)
{
	t_token *temp;
	// t_token *head;
	t_mini *mini;

	mini = get_data();

	if (token->type == REDIR_IN || token->type == REDIR_DBL){
		temp = token;
		redir(token);
		exec(temp);
	}
	else if (token->type == REDIR_OUT)
		redir2(token);
	else if (token->type == REDIR_DBL2)
		heredoc(token);
	else if (token->type == -3)
		do_pipe3(token);
	else if (token->type == PIPE && !ft_strncmp(mini->tokens->cmd[0], "cat", 4))
	{
		do_pipe_cat(token);

	}
	else if (token->type == PIPE || (token->next && !ft_strncmp(token->next_sep, "|", 1)))
		do_pipe(token);
	else if (token->type == ABS)
		absolute_path(token);
	else if (!ft_strncmp(token->cmd[0], "echo", 5))
		ft_echo(token);
	else if (!ft_strncmp(token->cmd[0], "pwd", 4))
		ft_pwd(token);
	else
		exec(token);
		
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
	// wait_pids(token);
	if (is_empty(token->cmd[0]))
	{
		command_not_found(token->cmd[0]);
		if (token->next)
			exec_and_stuff(token->next);
	}
	else if (!ft_builtins(head))
	{
		pid = fork();
		if (!pid){
			// ft_printf("e_and_s child: -*%d*-\n", head->pid);
			do_child_stuff(head);
			// wait_pids(head);
			// exec_and_stuff2(token->next);
			// free_child(token->mini);
			exit(0);
			
		}
		else
		{
			head->child_pid = pid;
			// ft_printf("e_and_s fork_pid: -*%d*-\n", head->child_pid);
			// ft_printf("e_and_s head->pid: -*%d*-\n", head->pid);
			// if (token->token_no == mini->no_of_tokens || token->token_no == 0){

				// printf("wait : %d", pid);
				waitpid(pid , NULL, 0);
				// printf("\n");
			wait_pids(head);
			// }
			// printf("wait : %d", pid + 1);
			// waitpid(pid + 1, NULL, 0);
			// printf("\n");
			// if (token->token_no == mini->no_of_tokens)
		}
		// if (token->next && token->next->type == REDIR_OUT)
		// 	exec_and_stuff(token->next);
		if (token->next && token->next->next && token->type == REDIR_IN)
			{
				// if(ft_strncmp(token->next->next->cmd[0], "cat", 3) != 0 && ft_strncmp(token->next->next->cmd[0], "wc", 3) != 0)/////////// patch
				exec_and_stuff(token->next->next);
			}
		// waitpid(pid, NULL, 0);
	}
}
void	exec_and_stuff2(t_token *token)
{
	t_token	*head;
	t_mini	*mini;

	mini = get_data();

	if (token->token_no == mini->no_of_tokens || token->token_no == 0){
				// printf("wait : %d", token->pid);
				waitpid(token->pid , NULL, 0);
				// printf("\n");
	}
	if (token == NULL)
		return ;
	head = token;
	if (is_empty(head->cmd[0]))
	{
		command_not_found(head->cmd[0]);
		if (head->next)
			exec_and_stuff(head->next);
	}
	else if (!ft_builtins(head)){

		if (token->token_no == mini->no_of_tokens){

		}
		do_child_stuff(head);
		
		// wait_pids(token);
	}
		// if (token->next && token->next->type == REDIR_OUT)
		// 	exec_and_stuff(token->next);
		// if (token->next && token->next->next && token->type == REDIR_IN)
		// 	{
		// 		// if(ft_strncmp(token->next->next->cmd[0], "cat", 3) != 0 && ft_strncmp(token->next->next->cmd[0], "wc", 3) != 0)/////////// patch
		// 		exec_and_stuff(token->next->next);
		// 	}
	}

