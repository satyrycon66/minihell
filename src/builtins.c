/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 08:34:53 by alpicard          #+#    #+#             */
/*   Updated: 2024/01/17 14:20:21 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	arg_count(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	ft_pwd(t_token *token)
{
	char	cur_dir[100];

	getcwd(cur_dir, 100);
	free(token->cmd[0]);
	token->cmd[0] = ft_strdup(cur_dir);
	ft_putendl_fd(cur_dir, 1);
	return (1);
}

int	ft_echo(t_token *token)
{
	int	i;
	int	j;
	int	n_option;

	i = 1;
	n_option = -1;
	j = 1;
	if (!token->cmd[1] || token->cmd[1] == NULL)
	{
		write(1, "\n", 1);
		return (1);
	}
	while (token->cmd[i] && !ft_strncmp(token->cmd[i], "-n", 2) && n_option != 0)
	{
			n_option = 1;
		while(token->cmd[i][j] == 'n')
			j++;
		if (ft_isalnum(token->cmd[i][j]))
		{
			i--;
			n_option = 0;
		}
		i++;
		
	}
	while (token->cmd[i])
	{
		ft_putstr_fd(token->cmd[i], 1);
		if (token->cmd[i + 1] && token->cmd[i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
	if (n_option <= 0)
		write(1, "\n", 1);
	return (1);
}

int	ft_unset(t_token *token)
{
	char		*part;
	int 		cmd_no;
	int			len;
	t_environ	*head;
	t_mini *mini;

	mini = get_data();
	if (!token->cmd[1] || !token->cmd[1][0])
		return (0);
	cmd_no = 1;
	while (token->cmd[cmd_no])
	{

	part = (token->cmd[cmd_no]);
	len = ft_strlen(part);
	head = token->mini->env_test;
	while (token->mini->env_test->next && ft_strncmp(part,
			token->mini->env_test->next->env_var, len) != 0)
		token->mini->env_test = token->mini->env_test->next;
	if (token->mini->env_test->next != NULL)
	{
		free(token->mini->env_test->next->env_var);
		free(token->mini->env_test->next->env_val);
		token->mini->env_test->next = token->mini->env_test->next->next;
	}
	token->mini->env_test = head;
	token->mini->env_len--;
	cmd_no++;
	}
	return (0);
}

int	ft_builtins(t_token *token)
{
	t_mini	*mini;

	mini = get_data();
	if (!ft_strncmp(token->cmd[0], "cd", 2))
		ft_cd(mini, token);
	else if (!ft_strncmp(token->cmd[0], "unset", 5))
		ft_unset(token);
	else if (!ft_strncmp(token->cmd[0], "export", 6) && !token->cmd[1])
		ft_export(mini, NULL);
	else if (!ft_strncmp(token->cmd[0], "export", 6))
		ft_export(mini, &token->cmd[1]);
	else if (!ft_strncmp(token->cmd[0], "env", 3))
		ft_env(token);
	else
		return (0);
	return (1);
}
