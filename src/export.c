/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 08:01:37 by alpicard          #+#    #+#             */
/*   Updated: 2024/01/17 13:56:05 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_export	*ft_exp(t_mini *mini, char *var)
{
	t_export	*export;

	(void)mini;
	export = malloc(sizeof(t_export));
	if (!export)
		return (NULL);
	export->temp = ft_split(var, '=');
	export->env_var = ft_strdup(export->temp[0]);
	export->env_val = ft_strdup(&var[ft_strlen(export->env_var) + 1]);
	export->next = NULL;
	releaser(export->temp);
	return (export);
}

int	check_export(char **var)
{
	int	x;
	int	ret;

	x = 0;
	ret = 1;
	if (!var || !var[0])
		return (0);
	while (var[x])
	{
		if ((var[x][0] == 0) || !ft_isalpha(var[x][0]))
		{
			ft_putstr_fd("Minishell: export: ", 2);
			ft_putstr_fd(var[x], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			ret = 0;
		}
		x++;
	}
	return (ret);
}

void init_export(t_mini *mini, char **var)
{
	t_export	*export_head;
	int			x;

	x = 0;
	mini->export = ft_exp(mini, var[x]);
	export_head = mini->export;
	while (var[++x])
	{
		mini->export->next = ft_exp(mini, var[x]);
		mini->export = mini->export->next;
	}
	mini->export->next = NULL;
	mini->export = export_head;
}

int	export_no_input(t_mini *mini)
{
	t_environ	*head;

	head = mini->env_test;
	while (head)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(head->env_var, 1);
		ft_putstr_fd("=", 1);
		ft_putchar_fd(34, 1);
		ft_putstr_fd(head->env_val, 1);
		ft_putchar_fd(34, 1);
		ft_putstr_fd("\n", 1);
		head = head->next;
	}
	return (0);
}

void	do_export(t_mini *mini, t_export *export, char **var)
{
	int			x;
	char		*temp;
	t_environ	*head_new;
	t_export *head;
	(void)export;
	x = 0;	
	head = mini->export;
	while (mini->export != NULL)
	{
		temp = get_env_part(mini, mini->export->env_var);
		if (temp[0] != '\0')
		{
			update_env_part2(mini, mini->export->env_var, mini->export->env_val);
			free(temp);
			x++;
		}
		else
		{
			head_new = new_env2(var[x++]);
			head_new->num = x;
			ft_envadd_back(&mini->env_test, head_new);
			// ajout de simon free
			// free(head_new);
			// free_env(head_new);
			free(temp);
		}
		mini->export = mini->export->next;
	}
	mini->export = head;
	// free_export(mini->export);
}
