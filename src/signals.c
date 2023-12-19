/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siroulea <siroulea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 06:14:32 by alpicard          #+#    #+#             */
/*   Updated: 2023/12/15 14:27:59 by siroulea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_int_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_quit_handler2(int sig)
{
	(void)sig;
	kill(0, 0);
}

void	ft_int_handler2(int sig)
{
	(void)sig;
	ft_putstr_fd("^C\n", 1);
	rl_on_new_line();
	kill(0, 0);
}

void	init_signals(int mode)
{
	if (mode == INTERACTIVE)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &ft_int_handler);
	}
	else if (mode == CHILD)
	{
		signal(SIGQUIT, &ft_quit_handler2);
		signal(SIGINT, &ft_int_handler2);
	}
}
