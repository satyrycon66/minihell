/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:22:48 by siroulea          #+#    #+#             */
/*   Updated: 2023/12/11 14:58:52 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	has_equal_sign(char **var)
{
	int	var_wrd;
	int	var_char;

	var_wrd = 0;
	var_char = 0;
	if (!var)
		return (0);
	if (!(var[0][0] == 0) && !ft_isalpha(var[0][0]))
		return (0);
	while (var[var_wrd])
	{
		var_char = 0;
		while (var[var_wrd][var_char])
		{
			if (var[var_wrd][var_char] == '=')
				return (1);
			var_char++;
		}
		var_wrd++;
	}
	return (0);
}

t_environ	*new_env(char **var)
{
	t_mini		*mini;
	t_environ	*new_env;
	t_environ	*head;
	int			x;

	mini = get_data();
	x = 0;
	new_env = init_item(var[x]);
	new_env->num = mini->env_len + x;
	head = new_env;
	x++;
	while (var[x] != NULL)
	{
		new_env->next = init_item(var[x]);
		new_env = new_env->next;
		new_env->num = mini->env_len + x;
		mini->env_len += x;
		x++;
	}
	new_env->next = NULL;
	new_env = head;
	return (new_env);
}

t_environ	*new_env2(char *var)
{
	t_mini		*mini;
	t_environ	*new_env;

	mini = get_data();
	new_env = init_item(var);
	mini->env_len++;
	new_env->next = NULL;
	return (new_env);
}

int	ft_export(t_mini *mini, char **var)
{
	t_export	*export;

	if (!var || !var[0] || !var[0][0])
		return (export_no_input(mini));
	if (!check_export(var) || !has_equal_sign(var))
		return (0);
	export = init_export(mini, var);
	do_export(mini, export, var);
	free_export(export);
	return (0);
}

int	is_builtin(t_token *token)
{
	if (!ft_strncmp(token->cmd[0], "pwd", 3))
		return (1);
	else if (!ft_strncmp(token->cmd[0], "PWD", 3))
		return (0);
	else if (!ft_strncmp(token->cmd[0], "cd", 2))
		return (1);
	else if (!ft_strncmp(token->cmd[0], "unset", 5))
		return (1);
	else if (!ft_strncmp(token->cmd[0], "export", 6) && !token->cmd[1])
		return (1);
	else if (!ft_strncmp(token->cmd[0], "export", 6))
		return (1);
	else if (!ft_strncmp(token->cmd[0], "env", 3))
		return (1);
	else if (!ft_strncmp(token->cmd[0], "echo", 5))
		return (0);
	else
		return (0);
}
