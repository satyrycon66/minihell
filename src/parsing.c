/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:59:47 by alpicard          #+#    #+#             */
/*   Updated: 2024/01/17 13:45:21 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_mini_no_wrds(void)
{
	t_mini	*mini;
	int		no_words;

	no_words = 0;
	mini = get_data();
	while (mini->cmds[no_words])
		no_words++;
	mini->no_wrds = no_words;
}

int	parse_mini_cmds(t_mini *mini)
{
	int	no_words;
	int	cmd_no;

	no_words = 0;
	cmd_no = -1;
	if (!mini->cmds[no_words] || !mini->cmds)
		return (0);
	set_mini_no_wrds();
	if (is_empty(mini->cmds[0]))
		return (0);
	return (1);
}

int	check_input(t_mini *mini)
{
	int	x;

	x = 0;

	while (mini->cmds[x])
	{
		if (is_sep2(mini->cmds[x]) && (!mini->cmds[x + 1] || !mini->cmds[x
					+ 1][0]|| is_sep2(mini->cmds[0]) ))
		{
			ft_putstr_fd("minishell: syntax error\n", 2);
			g_errno = 258;
			releaser(mini->cmds);
			return (0);
		}
		if (!check_pipe(mini, x))
			return (0);
		x++;
	}
	return (1);
}

int	ft_exit(char **cmds)
{
	if (cmds[1] && cmds[1][0])
	{
		if (!ft_isdigit(cmds[1][0]))
		{
			ft_putendl_fd("exit", 2);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmds[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			return (-2);
		}
		if (cmds[2] && cmds[2][0])
		{
			ft_putendl_fd("exit", 2);
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			return (0);
		}
	}
	return (-1);
}

int	ft_parse(t_mini *mini)
{
	if (!check_valid_quotes(mini->input))
	{
		ft_putendl_fd("Invalid Input", 2);
		return (0);
	}
	mini->no_wrds = no_of_words(mini->input, 0, 0, 0) + 1;
	mini->cmds = mini_split(mini->input);
	if (!mini->cmds || mini->cmds == NULL)
		return (0);
	if (!check_input(mini))
		return (0);
	if (!parse_mini_cmds(mini))
		return (0);
	if (!tokeniser(mini))
		return (0);
	if (!ft_strncmp(mini->tokens->cmd[0], "exit", 5))
		return (ft_exit(mini->tokens->cmd));
	return (1);
}
