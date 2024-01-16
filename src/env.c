/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 08:06:25 by alpicard          #+#    #+#             */
/*   Updated: 2024/01/16 14:38:13 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_env(t_token *token)
{
	print_env(token->mini->env_test);
	return (1);
}

void	ft_envadd_back(t_environ **env, t_environ *neo)
{
	t_environ	*temp;

	if (*env == NULL)
		*env = neo;
	else
	{
		temp = ft_envlast(*(env));
		temp->next = neo;
	}
}

t_environ	*ft_envlast(t_environ *env)
{
	t_environ *head = env;
	while (head)
	{
		if (head->next == NULL)
			return (head);
		head = head->next;
	}
	return (head);
}
