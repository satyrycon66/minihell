/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siroulea <siroulea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 20:20:09 by alpicard          #+#    #+#             */
/*   Updated: 2023/12/20 14:25:52 by siroulea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	no_of_words(char *s, int trigger, int i, int no_wrds)
{
	if (s[i] == 39)
	{
		i++;
		no_wrds++;
		trigger = 2;
	}
	else if (s[i] == 34)
	{
		i++;
		no_wrds++;
		trigger = 1;
	}
	while (s[i])
	{
		if (s[i] == ' ' && trigger == 0)
			no_wrds++;
		else if (s[i] == 34 && trigger == 1)
			no_wrds += 2;
		else if (s[i] == 39 && trigger == 2)
			no_wrds += 2;
		else if ((is_char_sep(s[i]) || (s[i + 1] && (is_char_sep(s[i + 1]))))
			&& trigger == 0)
			no_wrds += 2;
		i++;
	}
	return (no_wrds + 1);
}

int	mini_len(char *s, int start, int trigger, int len)
{
	while (s[start])
	{
		if (s[start] == ' ' && trigger == 0)
			return (len);
		else if (s[start] == 34 && trigger == 1)
			return (len + 1);
		else if (s[start] == 39 && trigger == 2)
			return (len + 1);
		else if (is_char_sep(s[start]) && s[start + 1] && !is_char_sep(s[start
					+ 1]) && trigger == 0)
		{
			return (len);
		}
		else if (is_char_sep(s[start]) && s[start + 1] && is_char_sep(s[start
					+ 1]) && trigger == 0)
		{
			return (len);
		}
		len++;
		start++;
	}
	return (len);
}

int	word_len(char *s, int start)
{
	int	trigger;
	int	len;

	trigger = 0;
	len = 0;
	if (s[start] == '<' && s[start + 1] && s[start + 1] == '<')
		return (2);
	if (s[start] == '>' && s[start + 1] && s[start + 1] == '>')
		return (2);
	if (s[start] == '|' || s[start] == '<' || s[start] == '>')
		return (1);
	if (s[start] == 39)
	{
		start++;
		len++;
		trigger = 2;
	}
	else if (s[start] == 34)
	{
		start++;
		len++;
		trigger = 1;
	}
	len = mini_len(s, start, trigger, len);
	return (len);
}

char	*substr(char *s, int start, int len)
{
	char	*str;
	int		i;

	i = 0;
	if (!s || !s[0] || len < 1 || start > (int)ft_strlen(s))
		return (NULL);
	if (len > (int)(ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	while (i < len && s[start])
	{
		str[i++] = s[start++];
	}
	str[i] = 0;
	return (str);
}

char	**no_name(char *s, int wrd_no, int no_wrds, char **split)
{
	int	len;
	int	i;

	i = 0;
	while (++wrd_no < no_wrds)
	{
		while (s[i] && s[i] == ' ')
			i++;
		len = word_len(s, i);
		split[wrd_no] = ft_substr(s, i, len);
		if (split[wrd_no][0] == '\0')
		{
			free(split[wrd_no]);
			split[wrd_no] = NULL;
			return (split);
		}
		i += len;
	}
	split[wrd_no] = NULL;
	return (split);
}

char	**mini_split(char *s)
{
	char	**split;
	int		no_wrds;
	int		wrd_no;

	no_wrds = no_of_words(s, 0, 0, 0) + 1;
	split = malloc(sizeof(char *) * no_wrds);
	if (!split)
		return (NULL);
	wrd_no = -1;
	return (no_name(s, wrd_no, no_wrds, split));
}
