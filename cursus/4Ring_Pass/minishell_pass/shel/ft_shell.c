/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:11:41 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/19 10:25:59 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "executor.h"
#include "syntax.h"
#include "list.h"
#include "parser.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

void	sig_handler(int signum)
{
	if (signum == 2 && g_global.pid == 0)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signum == 2 && g_global.pid != 0)
	{
		printf("\n");
		rl_on_new_line();
	}
	if (signum == 3 && g_global.pid != 0)
	{
		printf("Quit: 3\n");
	}
}

//USADO
void	ft_execute_line(char *readl, t_execution *exe)
{
	t_list		**lcommands;
	t_list		*tokenslinkedlist;

	lcommands = NULL;
	tokenslinkedlist = ft_lexer(readl);
	lcommands = ft_parse(tokenslinkedlist);
	if (ft_command_checker(lcommands))
		ft_execute(lcommands, exe);
	ft_freelist2d(lcommands);
}

void	ft_init(t_execution *exe, char **envp)
{
	g_global.pid = 0;
	exe->envp = NULL;
	exe->envp = ft_words_to_list(envp, exe->envp);
	rl_catch_signals = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}

int	main(int argc, char *argv[], char**envp)
{
	char					*readl;
	t_execution				exe;

	argc = 0;
	argv = 0;
	ft_init(&exe, envp);
	while (1)
	{
		g_global.pid = 0;
		readl = readline("microshell> ");
		if (!readl)
			break ;
		if (ft_strcontainstext(readl) == 1)
		{
			add_history(readl);
			if (ft_isvalidquotes(readl) && ft_forbidden_char(readl))
				ft_execute_line(readl, &exe);
		}
		free(readl);
	}
	ft_freelist(exe.envp);
	return (0);
}
