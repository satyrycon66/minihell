/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 08:54:27 by alpicard          #+#    #+#             */
/*   Updated: 2023/12/10 17:14:20 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_token(t_mini *mini)
{
	t_token	*head;

	head = mini->tokens;
	ft_printf("\n\t:TOKENS:\n_____________________\n");
	while (head != NULL)
	{
		ft_printf("token %d: type: %d\n", head->token_no, head->type);
		display_split(head->cmd, "\tcmd");
		ft_printf("\nnext sep: %s\n_____________________\n", head->next_sep);
		head = head->next;
	}
}
