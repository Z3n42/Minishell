/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:40:26 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/19 12:59:23 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	ft_execute_fork(t_list *command, t_execution *exe)
{
	char	*path;
	char	**env;
	char	**args;

	if (command->token == NULL)
	{
		printf("bash: : command not found\n");
		exit(127);
	}
	args = ft_list_to_char_table(command);
	path = ft_get_path(command, exe, args);
	env = ft_list_to_char_table(exe->envp);
	if (path)
		execve(path, args, env);
	printf("bash: %s: command not found\n", args[0]);
	ft_free_chartable(args);
	ft_free_chartable(env);
	free(path);
	exit(127);
}

void	ft_execute_not_builtin(t_list *command, t_execution *exe, int i)
{
	exe->total_f = exe->total_f + 1;
	g_global.pid = fork();
	if (g_global.pid == 0)
	{
		ft_default_pipes(exe, i);
		ft_dup_output(exe);
		ft_dup_input(exe);
		ft_close_pipes(exe->pipes, exe);
		if (ft_strequals(command->token, "echo"))
			ft_echo(command);
		else if (ft_strequals(command->token, "pwd"))
			ft_pwd();
		else if (ft_strequals(command->token, "env"))
			ft_env(exe);
		else
		{
			ft_execute_fork(command, exe);
		}
		exit(0);
	}
}

void	ft_execute_aux_2(t_list *command, t_execution *exe, int i)
{
	ft_str_to_lower(command->token);
	ft_clean_quote(command, exe->envp);
	if (ft_strequals(command->token, "cd"))
		ft_cd(command, exe);
	else if (ft_strequals(command->token, "export"))
		ft_export(command, exe);
	else if (ft_strequals(command->token, "unset"))
		ft_unset(command, exe);
	else if (ft_strequals(command->token, "exit"))
		ft_exit(command);
	else
		ft_execute_not_builtin(command, exe, i);
}

void	ft_execute_aux(t_list **lcommands, t_execution *exe, int command_n)
{
	lcommands[command_n] = ft_check_input(lcommands[command_n], exe);
	lcommands[command_n] = ft_output(lcommands[command_n], exe);
	if (lcommands[command_n])
		ft_execute_aux_2(lcommands[command_n], exe, command_n);
	if (exe->in_redi == 1)
	{
		free(exe->inputfile);
		free(exe->inputpath);
	}
	if (exe->in_redi == 2)
		free(exe->inputfile);
	if (exe->redi == 1 || exe->redi == 2)
		free(exe->outputfile);
}

int	ft_execute(t_list **lcommands, t_execution *exe)
{
	int	command_n;
	int	status;

	command_n = 0;
	status = -1;
	exe->total_f = 0;
	exe->inputfile = NULL;
	ft_create_pipes(lcommands, exe);
	while (lcommands[command_n] != NULL)
	{
		ft_execute_aux(lcommands, exe, command_n);
		command_n++;
	}
	ft_close_pipes(exe->pipes, exe);
	command_n = 0;
	while (command_n < exe->total_f)
	{
		wait(&status);
		g_global.errnor = WEXITSTATUS(status);
		command_n++;
	}
	free(exe->pipes);
	free(exe->pids);
	return (0);
}
