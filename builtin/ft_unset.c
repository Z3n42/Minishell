/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:26:56 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/17 17:46:28 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_unset_error(char *err)
{
	printf("bash: export: `");
	printf("%s", err);
	printf("': not a valid identifier\n");
	g_global.errnor = 1;
}

void	ft_unset_aux(t_execution *exe, t_list *tmp)
{
	t_list	*node;
	char	*varname;

	if ((ft_isdigit(tmp->token[0]) == 1)
		|| (ft_strisalnum(tmp->token) == 0))
		ft_unset_error(tmp->token);
	else
	{
		varname = tmp->token;
		node = exe->envp;
		while (node)
		{
			if (ft_strstartwith(node->token, varname))
			{
				exe->envp = ft_del_node(exe->envp,
						ft_node_position(exe->envp, node));
				break ;
			}
			node = node->next;
		}
	}
}

void	ft_unset(t_list *command, t_execution *exe)
{
	t_list	*tmp;

	g_global.errnor = 0;
	if (command->next == NULL || command->next->token == NULL)
		return ;
	tmp = command->next;
	while (tmp)
	{
		ft_unset_aux(exe, tmp);
		tmp = tmp->next;
	}
}
