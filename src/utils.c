/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siroulea <siroulea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:24:30 by alpicard          #+#    #+#             */
/*   Updated: 2023/12/15 14:28:18 by siroulea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	display_split(char **s, char *str)
{
	int	x;

	x = 0;
	if (str == 0)
		str = "split";
	if (s[0] == NULL)
		ft_printf("\nCMD Empty\n");
	while (s[x])
	{
		ft_printf("%s[%d]<%s>\n", str, x, s[x]);
		x++;
	}
}

int	no_of_quotes(int max, char *s)
{
	int	no_q;
	int	i;

	no_q = 0;
	i = 0;
	while (s[i] && i < max)
	{
		if (s[i] == 34)
			no_q++;
		i++;
	}
	return (no_q);
}

int	no_of_squotes(int max, char *s)
{
	int	no_q;
	int	i;

	no_q = 0;
	i = 0;
	while (s[i] && i < max)
	{
		if (s[i] == 39)
			no_q++;
		i++;
	}
	return (no_q);
}

int	is_sep(char *str)
{
	int	i;
	int	trigger;

	trigger = 0;
	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == 34 || str[i] == 39)
		trigger = 1;
	while (str[i])
	{
		if (trigger == 0 && (str[i] == '|' || str[i] == '>' || str[i] == '<'
				|| (str[i] == '>' && str[i + 1] && str[i + 1] == '>')))
			return (1);
		i++;
	}
	return (0);
}

int	is_empty(char *input)
{
	int	i;

	i = 0;
	if (!input || !input[0] || input == NULL)
		return (1);
	while (input[i] && (isspace(input[i]) || input[i] == '|'))
	{
		if (input[i] == '|')
			return (syntax_error());
		i++;
	}
	if (input[i] == '\0')
		return (1);
	return (0);
}
