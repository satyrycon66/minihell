/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:45:24 by siroulea          #+#    #+#             */
/*   Updated: 2024/01/14 15:27:12 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// char	**build_redir2_cmd(t_token *token)
// {
// 	char	**cmd;
// 	int		cmd_no;
// 	int		cmd_index;

// 	cmd_no = 0;
// 	cmd_index = 0;
// 	cmd = malloc(sizeof(char *) * token_size(token) + 2);
// 	while (token->cmd[cmd_no])
// 		cmd[cmd_index++] = token->cmd[cmd_no++];
// 	cmd[cmd_index++] = token->next->cmd[0];
// 	cmd[cmd_index] = NULL;
// 	return (cmd);
// }

void	redir2(t_token *token)
{

	token->fd_in = open(token->next->cmd[0],O_RDWR , O_RDONLY, 0777);
	if (token->fd_in <= 0)
	{
		ft_putstr_fd("No such file dumbass\n", 2);
		close(token->fd_in);
		exit(0);
	}
	else
	{
		dup2(token->fd_in, 0);
		if (token->next->next)
			do_pipe2(token);
		exec(token);
	}
}
