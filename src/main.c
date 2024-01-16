/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 07:01:40 by alpicard          #+#    #+#             */
/*   Updated: 2024/01/16 12:21:01 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*releaser(char **table)
{
	int	i;

	i = 0;
	if (table)
	{
		while (table[i])
		{
			free(table[i]);
			i++;
		}
		free(table);
	}
	return (NULL);
}

int	init_minishell(char **env)
{
	t_mini	*mini;

	mini = get_data();
	mini->env = env;
	mini->cmds = NULL;
	set_env(mini, env);
	set_shlvl();
	update_env_part(mini, "OLDPWD", "/");
	return (1);
}

char	*get_prompt(char *prt)
{
	char	*line;
	t_mini *mini;
	mini = get_data();
	line = readline(prt);
	if (line)
	{
		add_history(line);
		return (line);
	}
	//ce else la pour le control d fonctionne
	else
	{
		//rajouter free
		free_env(mini->env_test);
		free(mini);
		exit(g_errno);
	}
		
	return (NULL);
}

void	run_minishell(t_mini *mini)
{
	// print_token(mini);
	init_signals(CHILD);
	exec_and_stuff(mini->tokens);
	wait_pids(mini->tokens);
	wait_c_pids(mini->tokens);
	free_tokens(mini->tokens);
}

int	main(int ac, char **av, char **env)
{
	static t_mini	*mini;
	int				parsing;

	(void)av;
	if (ac > 1)
		return (0);
	mini = get_data();
	g_errno = 0;
	init_minishell(env);
	while (1)
	{
		init_signals(INTERACTIVE);
		mini->input = get_prompt(PROMPT);
		if (!is_empty(mini->input))
		{
			parsing = ft_parse(mini);
			if (parsing < 0)
			{
				if (parsing == -1)
					ft_putendl_fd("exit", 2);
				free(mini->input);
				free_minishell(mini);
				return (g_errno);
			}
			else if (parsing > 0)
				run_minishell(mini);
		}
	
	}
	return (g_errno);
}




//cat < a | ls | cat -e    un cat de trop 
// 19 dec error

// ********** dans le pdf de correction **************************************

// "" | ""     ||  "    "  | "     "
//retourne pas derreur senser ecrire command not found

//    |
//senser ecrire syntax error

// ls < a      || cat < a	
//a : command not found

// ls > a | ls | cat -e
// ne fait pas le pipe apres redirection 

// /bin/ls -l | cat -e ne fait pas le "cat -e" fait pas de pipe en  gros

// **************** AUTRES *******************************************************


//echo -n- devrais ecrire '-n-'

//echo -n -n ne devrais pas ecrire -n mais rien, touchi comme test je trouve

//********** LEAKS *************************************************************

//encore des leaks dans export
//definitely lost: 41 bytes in 2 blocks
//indirectly lost: 15 bytes in 2 blocks

//leaks dans unset aussi
// 2 block de plus dans indirectly

// leaks dans $?
// 1 leaks

//echo $PATH
// 2 leaks

//unset PATH 
//leaks 9 block

//still reachable et un fd si je cat << a et je sort avec control d
//normal jai pas free

// a verifier encore
// signaux heredoc


//**********************************************************************








//fonction pour le code d'erreur
// int	exit_code(int status)
// {
// 	int	res;

// 	res = 0;
// 	if (WIFEXITED(status))
// 		res = WEXITSTATUS(status);
// 	else if (WIFSIGNALED(status))
// 		res = WTERMSIG(status) + 128;
// 	return (res);
// }


