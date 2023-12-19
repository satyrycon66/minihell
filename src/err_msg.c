/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 09:18:36 by alpicard          #+#    #+#             */
/*   Updated: 2023/12/10 17:09:08 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_err_code(int code)
{
	g_errno = code;
}

int	syntax_error(void)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putendl_fd("syntax error", 2);
	g_errno = 258;
	return (258);
}

int	invalid_path(char *error)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(error, 2);
	ft_putendl_fd(" : No such file or directory", 2);
	return (0);
}

int	command_not_found(char *error)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(error, 2);
	ft_putendl_fd(" : command not found", 2);
	g_errno = 127;
	return (127);
}

int	is_a_directory(char *error)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(error, 2);
	ft_putendl_fd(" : is a directory", 2);
	return (0);
}
