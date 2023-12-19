/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:37:02 by siroulea          #+#    #+#             */
/*   Updated: 2023/12/11 19:45:12 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	update_env_part(t_mini *mini, char *part, char *_new)
{
	int			len;
	t_environ	*head;

	head = mini->env_test;
	len = ft_strlen(mini->env_test->env_var);
	while (mini->env_test && mini->env_test->env_var
		&& ft_strncmp(mini->env_test->env_var, part, len))
	{
		len = ft_strlen(mini->env_test->env_var);
		mini->env_test = mini->env_test->next;
	}
	if (mini->env_test && mini->env_test->env_val != NULL)
	{
		free(mini->env_test->env_val);
		mini->env_test->env_val = ft_strdup(_new);
		mini->env_test = head;
		return (1);
	}
	mini->env_test = head;
	return (1);
}

char	*check_part(char *part)
{
	char	*good_part;
	int		i;

	i = 0;
	if (!part || !part[0])
		return (0);
	good_part = malloc(ft_strlen(part) + 1);
	if (!good_part)
		return (NULL);
	i = 0;
	while (part[i] && part[i] != '$' && part[i] != 34 && part[i] != 39)
	{
		good_part[i] = part[i];
		i++;
	}
	good_part[i] = 0;
	return (good_part);
}

char	*get_env_part(t_mini *mini, char *part)
{
	t_environ	*head;
	int			part_len;

	if (!part || !part[0])
		return (NULL);
	head = mini->env_test;
	while (head != NULL)
	{
		part_len = ft_strlen(mini->env_test->env_var);
		if (!ft_strncmp(head->env_var, part, part_len))
			return (head->env_val);
		if (head->next != NULL)
			head = head->next;
		else
			return (ft_strdup("\0"));
	}
	return (ft_strdup("\0"));
}

int	env_size(t_environ *env)
{
	t_environ	*head;
	int			no_of_env_items;

	if (!env)
		return (0);
	no_of_env_items = 0;
	head = env;
	while (head)
	{
		no_of_env_items++;
		head = head->next;
	}
	return (no_of_env_items);
}

char	**env_l_to_dbl_arr(t_environ *env)
{
	t_environ	*head;
	int			no_of_env_items;
	int			env_item_no;
	char		**temp_env;
	char		*temp;

	env_item_no = 0;
	head = env;
	if (env == NULL || env->env_var == NULL)
		return (NULL);
	no_of_env_items = env_size(env);
	temp_env = malloc(sizeof(char *) * no_of_env_items + 1);
	if (!temp_env)
		return (NULL);
	while (head->next)
	{
		temp = ft_strjoin(head->env_var, "=");
		temp_env[env_item_no] = ft_strjoin(temp, head->env_val);
		env_item_no++;
		temp = ft_free(temp);
		head = head->next;
	}
	temp_env[env_item_no] = NULL;
	return (temp_env);
}
