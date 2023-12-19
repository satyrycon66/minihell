/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 08:17:36 by alpicard          #+#    #+#             */
/*   Updated: 2023/12/10 17:06:52 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**build_cmd(t_token *token)
{
	char	**s_cmd;
	char	**temp;
	int		cmd_no;

	cmd_no = 0;
	temp = ft_split(token->cmd[0], '/');
	while (temp[cmd_no])
		cmd_no++;
	s_cmd = malloc(sizeof(char *) * 3);
	if (!s_cmd)
		return (NULL);
	s_cmd[0] = temp[cmd_no - 1];
	if (token->cmd[1])
		s_cmd[1] = token->cmd[1];
	else
		s_cmd[1] = NULL;
	s_cmd[2] = NULL;
	free(temp);
	return (s_cmd);
}

void	exec_abs_path(char *path, t_token *token, char **s_cmd)
{
	char	**env;

	if (access(path, F_OK | X_OK) == 0)
	{
		env = env_l_to_dbl_arr(token->env);
		if (execve(path, s_cmd, env) < 0)
		{
			is_a_directory(s_cmd[0]);
			releaser(s_cmd);
			free(path);
		}
	}
	else
	{
		free(s_cmd);
		invalid_path(token->cmd[0]);
		free(path);
	}
}

void	absolute_path(t_token *token)
{
	char	*path;
	char	**s_cmd;

	s_cmd = NULL;
	path = malloc(100);
	if (!path || !token->cmd[0])
		return ;
	if (token->cmd[0][0] == '.')
	{
		getcwd(path, 100);
		path = ft_strjoin(path, "/");
		path = ft_strjoin(path, token->cmd[0]);
		s_cmd = build_cmd(token);
	}
	else
	{
		path = ft_strdup(token->cmd[0]);
		s_cmd = build_cmd(token);
	}
	exec_abs_path(path, token, s_cmd);
}
