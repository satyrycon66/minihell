/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siroulea <siroulea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 14:04:07 by alpicard          #+#    #+#             */
/*   Updated: 2023/12/13 12:05:55 by siroulea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*pre_dollar_sign(char *mini_cmd)
{
	char	*str;
	int		i;

	i = 0;
	if (has_dollar_sign(mini_cmd) == 0)
		return (ft_strdup("\0"));
	str = malloc(has_dollar_sign(mini_cmd));
	if (!str)
		return (NULL);
	while (mini_cmd && mini_cmd[i] && mini_cmd[i] != '$')
	{
		str[i] = mini_cmd[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*get_dollar_sign(char *mini_cmd)
{
	t_mini	*mini;
	char	*str;
	char	*dollar_sign;
	int		i;

	mini = get_data();
	i = has_dollar_sign(mini_cmd) + 1;
	str = check_part(&mini_cmd[i]);
	dollar_sign = ft_strdup(get_env_part(mini, str));
	return (dollar_sign);
}

int	dollar_len(char *mini_cmd)
{
	int	i;

	i = 0;
	while (mini_cmd && mini_cmd[i] && mini_cmd[i] != '$')
		i++;
	while (mini_cmd && mini_cmd[i] && !isspace(mini_cmd[i]))
	{
		i++;
		if (is_quote(mini_cmd[i]))
			return (i + 1);
	}
	return (i + 1);
}

char	*dollar_sign(char *mini_cmd)
{
	char	*dollar_sign;
	char	*pre_dollar;
	char	*get_dollar;
	int		len;

	if (mini_cmd[1] && mini_cmd[1] == '?')
		return (ft_itoa(g_errno));
	if (!mini_cmd[1])
		return (mini_cmd);
	pre_dollar = pre_dollar_sign(mini_cmd);
	get_dollar = get_dollar_sign(mini_cmd);
	dollar_sign = ft_strjoin(pre_dollar, get_dollar);
	len = dollar_len(mini_cmd);
	if (dollar_sign[0] && mini_cmd[len])
		dollar_sign = ft_strjoin(dollar_sign, &mini_cmd[len - 1]);
	free(pre_dollar);
	free(get_dollar);
	return (dollar_sign);
}

int	has_dollar_sign(char *input)
{
	int	i;

	i = 0;
	if (!input || !input[0])
		return (0);
	while (input[i])
	{
		if (input[i] == '$')
		{
			while (input[i + 1] && input[i + 1] == '$')
				i++;
			if (!input[i + 1])
				return (0);
			return (i);
		}
		i++;
	}
	return (0);
}
