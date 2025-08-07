/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 14:24:59 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/19 12:57:55 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

t_list	*ft_doc_here(t_list *command, t_list *act, t_execution *exe, int redi)
{
	int		i;
	char	*end;
	char	*input;
	char	*result;

	if (exe->in_redi == 1 || exe->in_redi == 2)
		free(exe->inputfile);
	exe->in_redi = redi;
	end = ft_strcpy(act->next->token);
	i = ft_node_position(command, act);
	command = ft_del_node(command, i);
	command = ft_del_node(command, i);
	input = readline("> ");
	result = NULL;
	while (ft_strequals(end, input) == 0)
	{
		result = ft_append_tostr(result, input);
		result = ft_append_tostr(result, "\n");
		free(input);
		input = readline("> ");
	}
	free(input);
	exe->inputfile = result;
	free(end);
	return (command);
}

t_list	*ft_set_input(t_list *command, t_list *act, t_execution *exe, int redi)
{
	int		i;
	char	*path;
	char	*file;

	if (exe->in_redi == 1 || exe->in_redi == 2)
	{
		free(exe->inputfile);
		free(exe->inputpath);
	}
	exe->in_redi = redi;
	file = ft_strcpy(act->next->token);
	i = ft_node_position(command, act);
	command = ft_del_node(command, i);
	command = ft_del_node(command, i);
	path = ft_strcpy(ft_getenv(exe->envp, "PWD"));
	path = ft_append_tostr(ft_append_tostr(path, "/"), file);
	exe->inputfile = ft_strcpy(file);
	exe->inputpath = ft_strcpy(path);
	free(file);
	free(path);
	return (command);
}

t_list	*ft_check_input(t_list *command, t_execution *exe)
{
	t_list		*act;
	t_list		*next;

	exe->in_redi = -1;
	act = command;
	while (act)
	{
		if (ft_strequals(act->token, "<"))
		{
			next = act->next->next;
			command = ft_set_input(command, act, exe, 1);
			act = next;
			if (exe->inputfile == NULL)
				break ;
		}		
		else if (ft_strequals(act->token, "<<"))
		{
			next = act->next->next;
			command = ft_doc_here(command, act, exe, 2);
			act = next;
		}
		else
			act = act->next;
	}
	return (command);
}
