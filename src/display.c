/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 08:54:27 by alpicard          #+#    #+#             */
/*   Updated: 2024/01/10 12:41:12 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_token(t_mini *mini)
{
	t_token	*head;

	head = mini->tokens;
	printf("\n\t:TOKENS:\n_____________________\n");
	while (head != NULL)
	{
		printf("token %d: type: %d\n", head->token_no, head->type);
		display_split(head->cmd, "\tcmd");
		printf("\nnext sep: %s\n_____________________\n", head->next_sep);
		head = head->next;
	}
}

void	display_split(char **s, char *str)
{
	int	x;

	x = 0;
	if (str == 0)
		str = "split";
	if (s[0] == NULL)
		printf("\nCMD Empty\n");
	while (s[x])
	{
		printf("%s[%d]<%s>\n", str, x, s[x]);
		x++;
	}
}