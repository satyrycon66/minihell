/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siroulea <siroulea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:45:24 by siroulea          #+#    #+#             */
/*   Updated: 2023/12/20 12:58:31 by siroulea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**build_redir2_cmd(t_token *token)
{
	char	**cmd;
	int		cmd_no;
	int		cmd_index;

	cmd_no = 0;
	cmd_index = 0;
	cmd = malloc(sizeof(char *) * token_size(token) + 2);
	while (token->cmd[cmd_no])
		cmd[cmd_index++] = token->cmd[cmd_no++];
	cmd[cmd_index++] = token->next->cmd[0];
	cmd[cmd_index] = NULL;
	return (cmd);
}

void	redir2(t_token *token)
{
	t_mini	*mini;
	char	*path;
	char	**cmd;
	char	**env;

	mini = get_data();
	token->fd_in = open(token->next->cmd[0], O_RDONLY, 0777);
	if (token->fd_in <= 0)
		ft_putstr_fd("No such file dumbass\n", 2);
	path = get_path(token);
	cmd = build_redir2_cmd(token);
	env = env_l_to_dbl_arr(mini->env_test);
	if ((execve(path, cmd, env) < 0))
	{
		free(cmd);
		command_not_found(token->cmd[0]);
		close(token->fd_hd);
		path = NULL;
		releaser(env);
	}
}
