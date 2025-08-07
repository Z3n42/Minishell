/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 12:52:35 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/17 17:54:56 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

t_list	*ft_set_output(t_list *command, t_list *act, t_execution *exe)
{
	int		i;
	char	*file;

	if (exe->redi == 1 || exe->redi == 2)
		free(exe->outputfile);
	if (ft_strequals(act->token, ">"))
		exe->redi = 1;
	else
		exe->redi = 2;
	file = ft_strcpy(act->next->token);
	i = ft_node_position(command, act);
	command = ft_del_node(command, i);
	command = ft_del_node(command, i);
	exe->outputfile = ft_strcpy(ft_getenv(exe->envp, "PWD"));
	exe->outputfile = ft_append_tostr(exe->outputfile, "/");
	exe->outputfile = ft_append_tostr(exe->outputfile, file);
	free(file);
	if (exe->redi == 1)
		close(open(exe->outputfile, O_RDWR | O_CREAT | O_TRUNC, 0755));
	else if (exe->redi == 2)
		close(open(exe->outputfile, O_RDWR | O_CREAT | O_APPEND, 0755));
	return (command);
}

t_list	*ft_output_init(t_list *command, t_execution *exe)
{
	exe->outputfile = NULL;
	exe->redi = -1;
	return (command);
}

t_list	*ft_output(t_list *command, t_execution *exe)
{
	t_list	*node;
	t_list	*next;

	node = ft_output_init(command, exe);
	while (node)
	{
		if (ft_strequals(node->token, ">") || ft_strequals(node->token, ">>"))
		{
			next = node->next->next;
			command = ft_set_output(command, node, exe);
			node = next;
		}
		else if (ft_strequals(node->token, "|"))
		{
			if (exe->redi == -1)
				exe->redi = 0;
			next = node->next;
			command = ft_del_node(command, ft_node_position(command, node));
			node = next;
		}
		else
			node = node->next;
	}
	return (command);
}
