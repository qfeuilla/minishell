/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 13:39:32 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/19 02:11:46 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_start()
{
	t_list	*token_list;
	t_list	*command_list;
	
	if ((token_list = prompt_loop(0)))
	{
		if (!tokens_syntax_check(token_list))
		{
			ft_lstclear(&token_list, free);
			ft_perror(ERR_UNFINISHED_QUOTE);
		}
		else
		{
			command_list = get_command_list(token_list);
			execute_pipes(&command_list);
			ft_lstclear(&token_list, free);
			free_commandlist(&command_list);
		}
	}
	else
		return ;
}

int	main(int argc, char **argv, char **env)
{
	open_pipe = 0;
	if (argc > 1 || argv[1])
	{
		ft_perror(ERR_TOO_MANY_ARGS);
		return (1);
	}
	g_env = env;
	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, sigquit_handler);
		if (!g_p_stop_sig)
			print_prompt();
		minishell_start();
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, sigquit_handler);
	}
	return (0);	
}